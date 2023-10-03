#ifndef _FREEBSD_BATTERY_H
#define _FREEBSD_BATTERY_H

int
getbatterylife(char* buf, size_t len);

int
getchargestate(char* buf, size_t len);

#endif
