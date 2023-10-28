package network

/*
#include <stdlib.h>

#include "network.h"
*/
import "C"

import (
  "unsafe"
)

func GetNetworkInfo() string {
  var (
    network     string
    
    cstrlen     C.size_t = 10
    cstr        *C.char = (*C.char)(C.malloc(cstrlen))
  )

  defer C.free(unsafe.Pointer(cstr))

  if C.getconnection(cstr, cstrlen) != 0 {
    return ""
  }

  network = C.GoString(cstr)

  return network
}
