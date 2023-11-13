#include <dirent.h>
#include <stdarg.h>
#include <string.h>

#include "battery.h"
#include "linux.h"

int
getbatterylife(char* buf, size_t len)
{
  char path[PATH_SIZE];
  int batteryID = getbatteryID();

  if (batteryID < 0) return 1;

  snprintf(path, PATH_SIZE, "%s%d/capacity", BATT_PATH, batteryID);

  FILE* batteryinfo = fopen(path, "r");
  if (batteryinfo == NULL) return cleanup(1, "Failed to open path", batteryinfo, NULL);

  if (fgets(buf, len, batteryinfo) != NULL) return cleanup(0, NULL, batteryinfo, NULL);
  
  return cleanup(1, NULL, batteryinfo, NULL);
}

int
getchargestate(char *buf, size_t len)
{
  char life[VAR_SIZE];
  char stat[VAR_SIZE];
  char lifepath[PATH_SIZE];
  char statpath[PATH_SIZE];
  int batteryID = getbatteryID();
  
  if (batteryID < 0) return 1;
  
  snprintf(lifepath, PATH_SIZE, "%s%d/capacity", BATT_PATH, batteryID);
  snprintf(statpath, PATH_SIZE, "%s%d/status", BATT_PATH, batteryID);
  
  FILE* batterylife = fopen(lifepath, "r");
  if (batterylife == NULL) return cleanup(1, "Failed to open battery life path", batterylife, NULL);
  
  FILE* batterystate = fopen(statpath, "r");
  if (batterystate == NULL) return cleanup(1, "Failed to open battery state path", batterylife, batterystate, NULL);
  
  if (fgets(life, VAR_SIZE, batterylife) == NULL) return cleanup(1, NULL, batterylife, batterystate, NULL);
  if (fgets(stat, VAR_SIZE, batterystate) == NULL) return cleanup(1, NULL, batterylife, batterystate, NULL);

  if (!strcmp(stat, "Charging\n")) snprintf(buf, len, "%s", CHARGE_BATT);
  
  else
  {
    int capacity = atoi(life);
  
    if (capacity >= 75) snprintf(buf, len, "%s", HIGH_BATT);
    else if (capacity >= 50) snprintf(buf, len, "%s", MED_BATT);
    else if (capacity >= 25) snprintf(buf, len, "%s", LOW_BATT);
    else snprintf(buf, len, "%s", CRIT_BATT);
  }

  return cleanup(0, NULL, batterylife, batterystate, NULL);
}

static int
checkpowersupply()
{
  struct dirent* entry;
  
  int empty = 1;
  DIR* powersupply = opendir(POWERSUPPLY_PATH);

  if (powersupply == NULL) return errorhandler("Could not open directory");

  while ((entry = readdir(powersupply)) != NULL)
  {
    if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))
    {
      empty = 0;
      break;
    }
  }

  closedir(powersupply);

  return empty;
}

static int
cleanup(int error, char* errormsg, FILE* file_arg, ...)
{
  va_list files;
  va_start(files, file_arg);

  FILE* file = file_arg;

  while (file != NULL)
  {
    fclose(file);
    file = va_arg(files, FILE*);
  }

  va_end(files);

  if (error) return errorhandler(errormsg);
  return 0;
}

static int
errorhandler(char* errormsg)
{
  if (errormsg != NULL) perror(errormsg);
  return 1;
}

static int
getbatteryID()
{
  if (checkpowersupply()) return -1;

  static int batteryID = 0;

  for (;;)
  {
    char path[PATH_SIZE];
    snprintf(path, PATH_SIZE, "%s%d", BATT_PATH, batteryID);

    DIR* dir = opendir(path);

    if (dir != NULL)
    {
      closedir(dir);
      return batteryID;
    }

    if (batteryID >= BATT_LIMIT)
    {
      closedir(dir);
      break;
    }
    
    batteryID++;
  }

  return -1;
}
