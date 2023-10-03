#ifndef _OPENBSD_BATTERY_H_
#define _OPENBSD_BATTERY_H_

int
getbatterylife(char* buf, size_t len);

int  
getchargestate(char* buf, size_t len);

#endif
