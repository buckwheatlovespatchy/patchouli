package datetime

import (
  "time"
)

const (
  layout = "2006-01-02 15:04:05"
)

func GetDate() string {
  var (
    current time.Time = time.Now()
    date    string    = current.Format(layout)
  )

  return date
}
