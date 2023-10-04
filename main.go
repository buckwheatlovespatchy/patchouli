package main

import (
  "flag"
  "fmt"
  "runtime"
  "os"
  "time"

  "chansoft/patchouli/pkg/battery"
  "chansoft/patchouli/pkg/util"
)

const version = "v0.0.1"

func main() {
  var (
    arch    string = runtime.GOARCH // not sure if entirely necessary or bloat yet
    userOS  string = runtime.GOOS   // same with this
    
    flagversion bool
    stat        string
  )

  flag.BoolVar(&flagversion, "v", false, "Patchouli version")
  flag.BoolVar(&flagversion, "version", false, "Patchouli version")

  flag.Usage = func() {
    fmt.Printf("Patchouli %s\nUsage: patchouli [optional args]\n\nFlags:\n", version)
    fmt.Printf("    -v, -version - Print current version of Patchouli\n    -h, -help - Print out this help menu\n")
  }

  flag.Parse()

  if flag.NFlag() > 1 {
    fmt.Printf("ERROR: Too many arguments passed - %d args were passed, maximum amount is 1\n", flag.NFlag())
    os.Exit(1)
  }

  if flagversion == true {
    fmt.Printf("Patchouli %s %s/%s\n", version, userOS, arch)
  } else {
    
    for {
      stat = fmt.Sprintf("[ Patchouli %s %s/%s | %s | %s %s ]", version, userOS, arch, util.GetDate(), battery.BatteryState(), battery.BatteryLife())
   
      err := util.SetStatbar(stat)
      if err != nil {
        panic(err)
      }

      time.Sleep(1 * time.Second)
    }

  }
}
