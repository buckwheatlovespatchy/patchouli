#ifndef _NETBSD_BATTERY_H_
#define _NETBSD_BATTERY_H_

#define WATTHOURS 1000000.0

#include <stdlib.h>
#include <sys/envsys.h>

int
getbatterylife(char* buf, size_t len);

int
getchargestate(char* buf, size_t len);

static int
cleanup(int sysmon_fd, int exitcode);

static int
getbatlifesensor(struct envsys_tre_data* sensorcheck, int sysmon_fd, size_t sensorcheck_size);

static int
getchargesensor(struct envsys_tre_data* sensorcheck, int sysmon_fd, size_t sensorcheck_size);

#endif
