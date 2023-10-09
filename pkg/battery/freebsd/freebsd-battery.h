#ifndef _FREEBSD_BATTERY_H
#define _FREEBSD_BATTERY_H

#define BATT_NOT_CHARGING 0
#define BATT_DISCHARGING 1
#define BATT_CHARGING 2
#define BATT_CRITICAL 4

#include <stdlib.h>

int
getbatterylife(char* buf, size_t len);

int
getchargestate(char* buf, size_t len);

#endif
