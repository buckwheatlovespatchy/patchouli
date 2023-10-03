#ifndef _NETBSD_BATTERY_H_
#define _NETBSD_BATTERY_H_

int
getbatterylife(char* buf, size_t len);

int
getchargestate(char* buf, size_t len);

static int
getbatlifesensor();

static int
getchargesensor();

#endif
