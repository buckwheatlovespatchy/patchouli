#ifndef _LINUX_NETWORK_H_
#define _LINUX_NETWORK_H_

#include <ifaddrs.h>
#include <stdlib.h>

static int
cleanuperrorhandler(struct ifaddrs* iface, const char* errmsg);

static int
getifacetype(const char* ifname, char* buf, size_t len);

static int
socketcleanup(int sock, int errcode, const char* errmsg);

#endif
