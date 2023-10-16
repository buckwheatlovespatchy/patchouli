#ifndef _NETWORK_H_
#define _NETWORK_H_

#define ETH "󰛳"
#define WIFI "󰀂"
#define OFFLINE "󰲛"

#include <ifaddrs.h>
#include <stdlib.h>

int
getconnection(char* buf, size_t len);

static int
cleanup(struct ifaddrs* iface, int exitcode);

static int
errorhandler(struct ifaddrs* iface, const char* errmsg);

static int 
getifacestat(struct ifaddrs* iface, char* buf, size_t len);

static void
getifacetype(struct ifaddrs* iface, const char* ifname, char* buf, size_t len);

#endif
