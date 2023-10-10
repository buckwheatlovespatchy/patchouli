#include <fcntl.h>
#include <machine/apmvar.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "battery.h"

int
getbatterylife(char* buf, size_t len)
{
  struct apm_power_info info;
  
  int apm_fd = open("/dev/apm", O_RDONLY);
 
  if (ioctl(apm_fd, APM_IOC_GETPOWER, &info) == -1) return 1;
  if (info.battery_state == APM_BATTERY_ABSENT || info.battery_state == APM_BATT_UNKNOWN) return 1;

  snprintf(buf, len, "%d", info.battery_life);
  
  close(apm_fd);

  return 0;
}

int
getchargestate(char* buf, size_t len)
{
  struct apm_power_info info;
  
  int apm_fd = open("/dev/apm", O_RDONLY);
 
  if (ioctl(apm_fd, APM_IOC_GETPOWER, &info) == -1) return 1;
  if (info.battery_state == APM_BATTERY_ABSENT || info.battery_state == APM_BATT_UNKNOWN) return 1;

  switch (info.battery_state) // Rewrite switch case to account for other charging states using man apm(4)
  {
    case APM_BATT_CHARGING:
      snprintf(buf, len, ">>");
      break;

    default:
      snprintf(buf, len, "==");
      break;
  }

  close(apm_fd);

  return 0;
}
