package util

/*
#cgo pkg-config: xcb

#include <stdlib.h>

#include "xorg.h"
*/
import "C"

import (
  "errors"
  "fmt"
  "reflect"
  "runtime"
  "unsafe"

  "chansoft/patchouli/pkg/config"
)

const (
  ARCH = runtime.GOARCH
  EMPTY = ""
  USER_OS = runtime.GOOS
  VERSION = "v0.0.2"
)

func getStatbar() string {
  var (
    batteryblock  int
    stat          string
  )

  if config.KEYMAP() == EMPTY {
    panic("Error! Could not get keymap! Please check your keyboard settings!")
  }

  for key, value := range config.BLOCK {
    isbattery := reflect.ValueOf(value).Pointer() == reflect.ValueOf(config.BATT).Pointer()

    if isbattery {
      if value() == EMPTY {
        batteryblock = key
      } else {
        batteryblock = 0
      }

      break;
    }
  } 

  switch (batteryblock) {
  case 0:  
    stat = fmt.Sprintf("[ %s | %s | %s | %s ]", config.BLOCK[1](), config.BLOCK[2](), config.BLOCK[3](), config.BLOCK[4]())
  
  case 1:
    stat = fmt.Sprintf("[ %s | %s | %s ]", config.BLOCK[2](), config.BLOCK[3](), config.BLOCK[4]())

  case 2:
    stat = fmt.Sprintf("[ %s | %s | %s ]", config.BLOCK[1](), config.BLOCK[3](), config.BLOCK[4]())

  case 3:
    stat = fmt.Sprintf("[ %s | %s | %s ]", config.BLOCK[1](), config.BLOCK[2](), config.BLOCK[4]())

  case 4:
    stat = fmt.Sprintf("[ %s | %s | %s ]", config.BLOCK[1](), config.BLOCK[2](), config.BLOCK[3]())

  default:
    panic("Error! Undefined key value! Please report this error immediately to the developer!")
  }
  
  return stat
}

func HelpMenu() {
  fmt.Printf("\033[1mPatchouli %s\033[0m\n", VERSION)
  fmt.Printf("\nUsage: patchouli [&/args]\n")
  fmt.Printf("\nFlags:\n    -h, --help - Print out this help menu\n    -v, --version - Print out the currently installed version of patchouli\n")
}

func SetStatbar() error {
  var (
    stat = getStatbar()

    statCString *C.char = C.CString(stat)

    errCode int
  )

  defer C.free(unsafe.Pointer(statCString))

  errCode = int(C.setstatbar(statCString))
  if errCode != 0 {
    return errors.New("Failed to set status bar in dwm")
  }

  return nil
}
