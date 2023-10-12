package main

import (
  "flag"
  "fmt"
  "runtime"
  "os"
  "time"

  "chansoft/patchouli/pkg/battery"
  "chansoft/patchouli/pkg/network"
  "chansoft/patchouli/pkg/util"
)

const version = "v0.0.1"

func main() {
  var (
    arch    string = runtime.GOARCH
    userOS  string = runtime.GOOS
    
    flagversion bool
    stat        string
  )

  flag.BoolVar(&flagversion, "v", false, "Patchouli version")
  flag.BoolVar(&flagversion, "version", false, "Patchouli version")

  flag.Usage = util.HelpMenu(version)
  
  flag.Parse()

  if flag.NFlag() > 1 {
    fmt.Printf("ERROR: Too many arguments passed - %d args were passed, maximum amount is 1\n", flag.NFlag())
    os.Exit(1)
  }

  if flagversion == true {
    fmt.Printf("Patchouli %s %s/%s\n", version, userOS, arch)
  } else {
    
    for {
      if battery.BatteryState() == "" && battery.BatteryLife() == "" {
        stat = fmt.Sprintf("[ %s | %s ]", network.NetworkInfo(), util.GetDate())
      } else {
        stat = fmt.Sprintf("[ %s | %s | %s %s ]", network.NetworkInfo(), util.GetDate(), battery.BatteryState(), battery.BatteryLife())
      }
   
      err := util.SetStatbar(stat)
      if err != nil {
        panic(err)
      }

      time.Sleep(1 * time.Second)
    }

  }
}
