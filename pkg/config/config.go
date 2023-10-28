package config

import (
  "chansoft/patchouli/pkg/battery"
  "chansoft/patchouli/pkg/datetime"
  "chansoft/patchouli/pkg/keymap"
  "chansoft/patchouli/pkg/network"
)

var (
  BATT    func() string = battery.GetBatteryString 
  DATE    func() string = datetime.GetDate
  KEYMAP  func() string = keymap.GetKeymap
  NET     func() string = network.GetNetworkInfo

  BLOCK map[int]func() string = map[int]func() string {
    1: NET,
    2: KEYMAP,
    3: DATE,
    4: BATT,
  }
)
