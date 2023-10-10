#include <fcntl.h>
#include <prop/proplib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "battery.h"

int
getbatterylife(char* buf, size_t len)
{
  struct envsys_tre_data battery_info;
  
  int sysmon_fd = open("/dev/sysmon", O_RDONLY);

  if (getbatlifesensor(&battery_info, sysmon_fd, sizeof(battery_info))) return cleanup(sysmon_fd, 1);
  if (ioctl(sysmon_fd, ENVSYS_GTREDATA, &battery_info)) return cleanup(sysmon_fd, 1);

  int battery = (((double)battery_info.cur.data_s / WATTHOURS) / ((double)battery_info.max.data_s / WATTHOURS)) * 100.0;

  snprintf(buf, len, "%d", battery);
  
  return cleanup(sysmon_fd, 0);
}

int
getchargestate(char* buf, size_t len)
{
  struct envsys_tre_data battery_info;
  struct envsys_tre_data charge_info;
  
  int sysmon_fd = open("/dev/sysmon", O_RDONLY);

  if (getbatlifesensor(&battery_info, sysmon_fd, sizeof(battery_info))) return cleanup(sysmon_fd, 1);
  if (ioctl(sysmon_fd, ENVSYS_GTREDATA, &battery_info)) return cleanup(sysmon_fd, 1);
  
  if (getchargesensor(&charge_info, sysmon_fd, sizeof(charge_info))) return cleanup(sysmon_fd, 1);
  if (ioctl(sysmon_fd, ENVSYS_GTREDATA, &charge_info)) return cleanup(sysmon_fd, 1);

  if (charge_info.units == ENVSYS_INDICATOR)
  {
    switch (charge_info.cur.data_s)
    {
      case ENVSYS_INDICATOR_TRUE:
        snprintf(buf, len, ">>");
        break;
      
      case ENVSYS_INDICATOR_FALSE: // Rewrite case to check for the current battery static_assert
        if (battery_info.warnflags) snprintf(buf, len, "!!");
        else snprintf(buf, len, "==");
        
        break;
      
      default:
        return cleanup(sysmon_fd, 1);
    }
  }

  return cleanup(sysmon_fd, 0);
}

static int
cleanup(int sysmon_fd, int exitcode)
{
  close(sysmon_fd);
  return exitcode;
}

static int
getbatlifesensor(struct envsys_tre_data* sensorcheck, int sysmon_fd, size_t sensorcheck_size)
{
  static int sensor = 0; // Value stays consistent thus preventing it from mutating across calls to getbatlifesensor() and speeding things up
  
  memset(sensorcheck, 0, sensorcheck_size);

  for (;;)
  {
    sensorcheck->sensor = sensor;

    if (ioctl(sysmon_fd, ENVSYS_GTREDATA, sensorcheck) == -1) exit(EXIT_FAILURE);
    if (sensorcheck->max.data_s || sensor == ENVSYS_MAXSENSORS) break; // Theoretically this should help prevent an unnecessary incrementing of sensor
    
    sensor++;
  }

  if (sensorcheck->max.data_s == 0) return 1;

  return 0;
}

static int
getchargesensor(struct envsys_tre_data* sensorcheck, int sysmon_fd, size_t sensorcheck_size)
{
  int batlifesensor;

  if (getbatlifesensor(sensorcheck, sysmon_fd, sensorcheck_size)) return 1;

  batlifesensor = sensorcheck->sensor + 3; // Theoretically should give us the charging sensor
  sensorcheck->sensor = batlifesensor;

  return 0;
}
