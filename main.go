package main

import (
  "flag"
  "fmt"
  "os"
  "time"

  "chansoft/patchouli/pkg/util"
)

func main() {
  var flagversion bool

  flag.BoolVar(&flagversion, "v", false, "Patchouli version")
  flag.BoolVar(&flagversion, "version", false, "Patchouli version")
  flag.Usage = util.HelpMenu
  
  flag.Parse()

  if flag.NFlag() > 1 {
    fmt.Printf("ERROR: Too many arguments passed - %d args were passed, maximum amount is 1\n", flag.NFlag())
    os.Exit(1)
  }

  if flagversion == true {
    fmt.Printf("Patchouli %s %s/%s\n", util.VERSION, util.USER_OS, util.ARCH)
  } else {
    
    for {
      err := util.SetStatbar()
      if err != nil {
        panic(err)
      }

      time.Sleep(1 * time.Second)
    }

  }
}
