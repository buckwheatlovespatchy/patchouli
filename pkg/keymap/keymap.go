package keymap

/*
#cgo pkg-config: xcb xcb-xkb

#include <stdlib.h>

#include "keymap.h"
*/
import "C"

import (
  "unsafe"
)

func GetKeymap() string {
  var (
    keymap string

    keymapCStrLen C.size_t = 6
    keymapCStr *C.char = (*C.char)(C.malloc(keymapCStrLen))
  )

  defer C.free(unsafe.Pointer(keymapCStr))

  if C.getkeymapname(keymapCStr, keymapCStrLen) != 0 {
    return ""
  }

  keymap = C.GoString(keymapCStr)

  return keymap
}
