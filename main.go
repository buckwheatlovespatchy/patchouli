package main

import (
  "flag"
  "fmt"
  "runtime"
  "os"
  "time"

  "chansoft/patchouli/pkg/config"
  "chansoft/patchouli/pkg/util"
)

const (
  empty   = "   "
  version = "v0.0.1"
)

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
      if config.BLOCK1() == empty {
        stat = fmt.Sprintf("[ %s | %s ]", config.BLOCK2(), config.BLOCK3())
      } else if config.BLOCK2() == empty {
        stat = fmt.Sprintf("[ %s | %s ]", config.BLOCK1(), config.BLOCK3())
      } else if config.BLOCK3() == empty {
        stat = fmt.Sprintf("[ %s | %s ]", config.BLOCK1(), config.BLOCK2())
      } else {
        stat = fmt.Sprintf("[ %s | %s | %s ]", config.BLOCK1(), config.BLOCK2(), config.BLOCK3())
      }
   
      err := util.SetStatbar(stat)
      if err != nil {
        panic(err)
      }

      time.Sleep(1 * time.Second)
    }

  }
}
