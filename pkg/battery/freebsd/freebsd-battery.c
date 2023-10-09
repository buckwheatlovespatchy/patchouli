#include <stdio.h>
#include <sys/sysctl.h>

#include "battery.h"

int
getbatterylife(char* buf, size_t len)
{
  int batterylife;
  size_t batterylife_size = sizeof(batterylife);

  if (sysctlbyname("hw.acpi.battery.life", &batterylife, &batterylife_size, NULL, 0) == -1) return 1;

  snprintf(buf, len, "%d", batterylife);

  return 0;
}

int
getchargestate(char* buf, size_t len)
{
  int chargestate;
  size_t chargestate_size = sizeof(chargestate);

  if (sysctlbyname("hw.acpi.battery.state", &chargestate, &chargestate_size, NULL, 0) == -1) return 1;

  switch (chargestate)
  {
    case BATT_NOT_CHARGING:
      snprintf(buf, len, "==");
      break;

    case BATT_DISCHARGING:
      snprintf(buf, len, "==");
      break;

    case BATT_CHARGING:
      snprintf(buf, len, ">>");
      break;

    case BATT_CRITICAL:
      snprintf(buf, len, "==");
      break;

    default:
      return 1;
  }
  
  return 0;
}