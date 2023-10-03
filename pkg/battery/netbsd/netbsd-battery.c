#include <fcntl.h>
#include <prop/proplib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/envsys.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "battery.h"

int
getbatterylife(char* buf, size_t len)
{
  struct envsys_tre_data battery_info;
  
  int sensor = getbatlifesensor();
  int sysmon_fd = open("/dev/sysmon", O_RDONLY);
  
  memset(&battery_info, 0, sizeof(battery_info));
  battery_info.sensor = sensor;

  if (ioctl(sysmon_fd, ENVSYS_GTREDATA, &battery_info) == -1) return 1;

  double cur = (double)battery_info.cur.data_s / 1000000.0;
  double max = (double)battery_info.max.data_s / 1000000.0;
  double battery = (cur / max) * 100.0;
  int batteryint = battery;

  snprintf(buf, len, "%d", batteryint);
  
  close(sysmon_fd);

  return 0;
}

int
getchargestate(char* buf, size_t len)
{
  struct envsys_tre_data charge_info;
  
  int sensor = getchargesensor();
  int sysmon_fd = open("/dev/sysmon", O_RDONLY);

  memset(&charge_info, 0, sizeof(charge_info));

  if (ioctl(sysmon_fd, ENVSYS_GTREDATA, &charge_info) == -1) return 1;

  if (charge_info.units == ENVSYS_INDICATOR)
  {
    switch (charge_info.cur.data_s)
    {
      case ENVSYS_INDICATOR_TRUE:
        snprintf(buf, len, ">>");
        break;
      
      case ENVSYS_INDICATOR_FALSE:
        snprintf(buf, len, "==");
        break;
      
      default:
        snprintf(buf, len, "??");
        break;
    }
  }

  close(sysmon_fd);

  return 0;
}

static int
getbatlifesensor()
{
  struct envsys_tre_data sensorcheck;

  static int sensor = 0; // Value stays consistent thus preventing it from mutating across calls to getbatlifesensor() and speeding things up
  int sysmon_fd = open("/dev/sysmon", O_RDONLY);
  
  memset(&sensorcheck, 0, sizeof(sensorcheck));

  for (sensor = 0; sensor < ENVSYS_MAXSENSORS; sensor++)
  {
    sensorcheck.sensor = sensor;

    if (ioctl(sysmon_fd, ENVSYS_GTREDATA, &sensorcheck) == -1) exit(EXIT_FAILURE);
    if (sensorcheck.max.data_s != 0) break; // Theoretically this should help prevent an unnecessary incrementing of sensor
  }

  close(sysmon_fd);

  if (sensorcheck.max.data_s == 0) return 0;

  return sensor;
}

static int
getchargesensor()
{
  int sensor;

  int batlifesensor = getbatlifesensor();

  if (batlifesensor == 0) return 0;

  sensor = batlifesensor + 3; // Theoretically based on the output of envstat, sensor should be batlifesensor + 3

  return sensor;
}
