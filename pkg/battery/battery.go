package battery

/*
#include <stdlib.h>

#include "battery.h"
*/
import "C"

import (
  "fmt"
  "unsafe"
)

func batteryLife() string {
  var (
    batterystr  string
    cstr        string

    batteryCLen    C.size_t = 6
    batteryCString *C.char  = (*C.char)(C.malloc(batteryCLen))
  )

  defer C.free(unsafe.Pointer(batteryCString))

  if C.getbatterylife(batteryCString, batteryCLen) != 0 {
    return ""
  }

  cstr = C.GoString(batteryCString)

  batterystr = fmt.Sprintf("%s%%", cstr)
   
  return batterystr
}

func batteryState() string {
  var (
    state string

    stateCLen    C.size_t = 5
    stateCString *C.char  = (*C.char)(C.malloc(stateCLen))
  )

  defer C.free(unsafe.Pointer(stateCString))

  if C.getchargestate(stateCString, stateCLen) != 0 {
    return ""
  }

  state = C.GoString(stateCString)

  return state
}

func GetBatteryString() string {
  if batteryState() == "" || batteryLife() == "" {
    return ""
  } else {
    return fmt.Sprintf("%s %s", batteryState(), batteryLife())
  }
}
