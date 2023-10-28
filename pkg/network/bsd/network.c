#include <arpa/inet.h>
#if defined __OpenBSD__ || defined __FreeBSD__
#include <netinet/in.h>
#include <net/if.h>
#endif
#include <net/if_dl.h>
#include <net/if_types.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "bsd.h"
#include "network.h"

int
getconnection(char* buf, size_t len)
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

      if (getifacestat(iface, ifaceconn, INET_ADDRSTRLEN)) return errorhandler(if_info, "Could not perform IP Address allocation to buffer");
      
      getifacetype(iface, ifname, buf, len);

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
errorhandler(struct ifaddrs* iface, const char* errmsg)
{
  perror(errmsg);
  return cleanup(iface, 1);
}

static int
getifacestat(struct ifaddrs* iface, char* buf, size_t len)
{
  struct sockaddr_in* ifaceaddr = (struct sockaddr_in*)iface->ifa_addr;

  if (inet_ntop(AF_INET, &ifaceaddr->sin_addr, buf, len) == NULL) return 1;

  return 0;
}

static void
getifacetype(struct ifaddrs* iface, const char* ifname, char* buf, size_t len)
{
  struct sockaddr_dl* iface_info = (struct sockaddr_dl*)iface->ifa_addr;

  switch (iface_info->sdl_type)
  {
    case IFT_ETHER:
      snprintf(buf, len, "%s %s", ETH, ifname);
      break;

    default:
      snprintf(buf, len, "%s %s", WIFI, ifname);
      break;
  }

}
