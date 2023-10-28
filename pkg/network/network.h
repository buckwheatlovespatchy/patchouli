#ifndef _NETWORK_H_
#define _NETWORK_H_

#if defined __NetBSD__ || defined __OpenBSD__
#define ETH "󰛳"
#define WIFI "󰀂"
#define OFFLINE "󰲛"
#else
#define ETH ""
#define WIFI "直"
#define OFFLINE ""
#endif

#include <ifaddrs.h>
#include <stdlib.h>

int
getconnection(char* buf, size_t len);

static int
cleanup(struct ifaddrs* iface, int exitcode);

static int 
getifacestat(struct ifaddrs* iface, char* buf, size_t len);

#endif
