#include <arpa/inet.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include "network.h"

int
getconnection(char *buf, size_t len)
{
  struct ifaddrs* if_info;
  char ifname[20];
  char ifaceconn[INET_ADDRSTRLEN];

  if (getifaddrs(&if_info)) return 1;

  for (struct ifaddrs* iface = if_info; iface != NULL; iface = iface->ifa_next)
  {
    if (iface->ifa_addr != NULL && iface->ifa_addr->sa_family == AF_INET)
    {
      if (strstr(iface->ifa_name, "lo")) continue;
      if (strstr(iface->ifa_name, "tun")) continue;

      snprintf(ifname, sizeof(ifname), "%s", iface->ifa_name);
      
      if (getifacestat(iface, ifaceconn, INET_ADDRSTRLEN)) return cleanuperrorhandler(if_info, "Could not perform IP Address allocation to buffer");
      if (getifacetype(ifname, buf, len)) return cleanuperrorhandler(if_info, "Could not identify interface type");

      break;
    }
  }
  
  if (!strcmp(ifaceconn, "")) snprintf(buf, len, "%s", OFFLINE);

  return cleanup(if_info, 0);
}

static int
cleanup(struct ifaddrs* iface, int exitcode)
{
  freeifaddrs(iface);
  return exitcode;
}

static int
cleanuperrorhandler(struct ifaddrs* iface, const char* errmsg)
{
  perror(errmsg);
  return cleanup(iface, 1);
}

static int
errorhandler(const char* errmsg)
{
  perror(errmsg);
  return 1;
}

static int
getifacestat(struct ifaddrs* iface, char* buf, size_t len)
{
  struct sockaddr_in* ifaceaddr = (struct sockaddr_in*)iface->ifa_addr;
  
  if (inet_ntop(AF_INET, &ifaceaddr->sin_addr, buf, len) == NULL) return 1;
  
  return 0;
}

static int
getifacetype(const char* ifname, char* buf, size_t len)
{
  struct ifreq ifacetype;
  int sock = socket(AF_INET, SOCK_DGRAM, 0);

  if (sock < 0) return errorhandler("Could not check network device info");

  strncpy(ifacetype.ifr_name, ifname, IFNAMSIZ);

  if (ioctl(sock, SIOCGIFHWADDR, &ifacetype) < 0) return socketcleanup(sock, 1, "Error with ioctl call");

  close(sock);

  switch (ifacetype.ifr_hwaddr.sa_family)
  {
    case ARPHRD_EETHER:
      snprintf(buf, len, "%s %s", ETH, ifname);
      break;

    default:
      snprintf(buf, len, "%s %s", WIFI, ifname);
      break;
  }

  return 0;
}

static int
socketcleanup(int sock, int errcode, const char* errmsg)
{
  close(sock);
  
  if (errcode) return errorhandler(errmsg);
  return 0;
}
