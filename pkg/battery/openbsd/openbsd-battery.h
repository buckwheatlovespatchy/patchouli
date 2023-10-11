#ifndef _OPENBSD_BATTERY_H_
#define _OPENBSD_BATTERY_H_

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

static int
cleanup(int apm_fd, int exitcode);

#endif
