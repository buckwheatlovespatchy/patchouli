#include <stdio.h>
#include <stdlib.h>
#include <sys/sysctl.h>

#include "battery.h"

int
getbatterylife(char *buf, size_t len)
{
  int batterylife;
  size_t batterylife_size;

  if (sysctlbyname("hw.acpi.battery.life", &batterylife, &batterylife_size, NULL, 0) == -1) return 1;

  snprintf(buf, len, "%d", batterylife);

  return 0;
}

int
getchargestate(char *buf, size_t len)
{
  int chargestate;
  size_t chargestate_size;

  if (sysctlbyname("hw.acpi.acline", &chargestate, &chargestate_size, NULL, 0) == -1) return 1;

  switch (chargestate)
  {
    case 0:
      snprintf(buf, len, "==");
      break;

    case 1:
      snprintf(buf, len, ">>");
      break;

    default:
      return 1;
  }
  
  return 0;
}