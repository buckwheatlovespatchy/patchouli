#ifndef _BATTERY_H_
#define _BATTERY_H_

#if defined __NetBSD__ || defined __OpenBSD__
#define HIGH_BATT "󱊣"
#define MED_BATT "󱊢"
#define LOW_BATT "󱊡"
#define CRIT_BATT "󰂃"
#define CHARGE_BATT "󰂄"
#else
#define HIGH_BATT ""
#define MED_BATT ""
#define LOW_BATT ""
#define CRIT_BATT ""
#define CHARGE_BATT ""
#endif

#include <stdlib.h>

int
getbatterylife(char* buf, size_t len);

int
getchargestate(char* buf, size_t len);

#endif
