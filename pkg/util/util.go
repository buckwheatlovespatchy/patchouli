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
  "time"
  "unsafe"
)

func GetDate() string {
  const layout = "2006-01-02 15:04:05"
  
  var (
    current time.Time = time.Now()
    date    string    = current.Format(layout)
  )

  return date
}

func HelpMenu(version string) {
  fmt.Printf("\033[1mPatchouli %s\033[0m\n", version)
  fmt.Printf("Usage: patchouli [&/args]\n")
  fmt.Printf("Flags:\n    help - Print out this help menu\n    version - Print out the currently installed version of patchouli\n")
}

func SetStatbar(stat string) error {
  var (
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
