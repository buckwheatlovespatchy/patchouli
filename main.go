package main

import (
  "fmt"
  //"os"
  "runtime"
  "time"

  "chansoft/patchouli/pkg/battery"
  "chansoft/patchouli/pkg/util"
)

const version = "v0.0.1"

func main() {
  var (
    arch    string = runtime.GOARCH // not sure if entirely necessary or bloat yet
    userOS  string = runtime.GOOS   // same with this

    stat          string
  )

  /*
  if len(os.Args) > 2 {
    
    fmt.Printf("ERROR: Too many arguments provided, user provided %d args when there can only be a single argument total", len(os.Args))
    os.Exit(1)

  } else if len(os.Args) == 1 {
    
    switch (os.Args[1]) {
      case "help":
      util.HelpMenu(version)

      case "version":
      fmt.Printf("Patchouli %s/%s %s\n", userOS, arch, version)

      default:
      fmt.Printf("ERROR: Argument %s not found", os.Args[1])
      os.Exit(1)
    }

  } else {
  */  
  for {
    stat = fmt.Sprintf("[ Patchouli %s %s/%s | %s | %s %s ]", version, userOS, arch, util.GetDate(), battery.BatteryState(), battery.BatteryLife())
   
    err := util.SetStatbar(stat)
    if err != nil {
      panic(err)
    }

    time.Sleep(1 * time.Second)
  }

  //}
}
