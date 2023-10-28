#ifndef _BSD_NETWORK_H_
#define _BSD_NETWORK_H_

#include <ifaddrs.h>
#include <stdlib.h>

static int
errorhandler(struct ifaddrs* iface, const char* errmsg);

static void
getifacetype(struct ifaddrs* iface, const char* ifname, char* buf, size_t len);

#endif
