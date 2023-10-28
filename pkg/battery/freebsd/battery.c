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
  int batterylife;
  size_t batterylife_size = sizeof(batterylife);
  int chargestate;
  size_t chargestate_size = sizeof(chargestate);

  if (sysctlbyname("hw.acpi.battery.life", &batterylife, &batterylife_size, NULL, 0) == -1) return 1;
  if (sysctlbyname("hw.acpi.battery.state", &chargestate, &chargestate_size, NULL, 0) == -1) return 1;

  switch (chargestate)
  {
    case 1:
      snprintf(buf, len, CHARGE_BATT);
      break;

    default:
      if (batterylife >= 75) snprintf(buf, len, HIGH_BATT);
      else if (batterylife >= 50) snprintf(buf, len, MED_BATT);
      else if (batterylife >= 25) snprintf(buf, len, LOW_BATT);
      else snprintf(buf, len, CRIT_BATT);
      
      break;
  }
  
  return 0;
}
