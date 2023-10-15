#ifndef _LINUX_BATTERY_H
#define _LINUX_BATTERY_H

#define BATT_LIMIT 3
#define BATT_PATH "/sys/class/power_supply/BAT"
#define VAR_SIZE 20
#define PATH_SIZE 50

#define HIGH_BATT "󱊣"
#define MED_BATT "󱊢"
#define LOW_BATT "󱊡"
#define CRIT_BATT "󰂃"
#define CHARGE_BATT "󰂄"

#include <stdio.h>
#include <stdlib.h>

int
getbatterylife(char* buf, size_t len);

int
getchargestate(char* buf, size_t len);

static int
cleanup(int error, char* errormsg, FILE* file_arg, ...);

static int
errorhandler(char* errormsg);

static int
getbatteryID();

#endif
