#ifndef _DRAGONFLYBSD_BATTERY_H_
#define _DRAGONFLYBSD_BATTERY_H_

int
getbatterylife(char* buf, size_t len);

int 
getchargestate(char* buf, size_t len);

#endif
