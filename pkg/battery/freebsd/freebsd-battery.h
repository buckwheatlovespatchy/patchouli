#ifndef _FREEBSD_BATTERY_H
#define _FREEBSD_BATTERY_H

#define HIGH_BATT "󱊣"
#define MED_BATT "󱊢"
#define LOW_BATT "󱊡"
#define CRIT_BATT "󰂃"
#define CHARGE_BATT "󰂄"

#include <stdlib.h>

int
getbatterylife(char* buf, size_t len);

int
getchargestate(char* buf, size_t len);

#endif
