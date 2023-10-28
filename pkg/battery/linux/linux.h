#ifndef _LINUX_BATTERY_H_
#define _LINUX_BATTERY_H_

#define BATT_LIMIT 3
#define BATT_PATH "/sys/class/power_supply/BAT"
#define PATH_SIZE 50
#define POWERSUPPLY_PATH "/sys/class/power_supply"
#define VAR_SIZE 20

#include <stdio.h>

static int
checkpowersupply();

static int
cleanup(int error, char* errormsg, FILE* file_arg, ...);

static int
errorhandler(char* errormsg);

static int
getbatteryID();

#endif
