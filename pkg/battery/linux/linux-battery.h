#ifndef _LINUX_BATTERY_H
#define _LINUX_BATTERY_H

int
getbatterylife(char* buf, size_t len);

int
getchargestate(char* buf, size_t len);

#endif
