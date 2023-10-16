package config

import (
  "chansoft/patchouli/pkg/battery"
  "chansoft/patchouli/pkg/network"
  "chansoft/patchouli/pkg/util"
)

var (
  BATT_BLOCK func() string = battery.GetBatteryString 
  DATE_BLOCK  func() string = util.GetDate
  NET_BLOCK   func() string = network.NetworkInfo

  BLOCK1     func() string = NET_BLOCK
  BLOCK2     func() string = DATE_BLOCK
  BLOCK3     func() string = BATT_BLOCK
)
