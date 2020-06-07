/*
  time related code snippets
*/

package timeutil

import (
	"fmt"
	"time"
)

var FormatNormal = "2006-01-02 15:04:05"
var FormatWithMs = "2006-01-02 15:04:05.000"
var FormatSimple = "20060102150405"
var FormatSimpleWithMs = "20060102150405000"
var FormatSimpleWithMsDot = "20060102150405.000"

// GetCurrentFormatedTime Format time string
func GetCurrentFormatedTime(format string) string{
	return GetFormatedTime(time.Now(), format)

	//t := time.Now()
	//fmt.Printf("%04d-%02d-%02d %02d:%02d:%02d %03d\n", t.Year(), int(t.Month()), t.Day(), t.Hour(), t.Minute(), t.Second(), t.Nanosecond()/1000000 )
}

// GetFormatedTime Format time string
func GetFormatedTime(t time.Time, format string) string{
	if format == FormatSimpleWithMs {
		return fmt.Sprintf("%v%v", t.Format(FormatSimple), t.Nanosecond() / int(time.Millisecond) )
	}

	return fmt.Sprintf("%v", time.Now().Format(format) )
}

// FormatInLocalZone 将时间字符串转为RFC3339格式的字符串
// oldFormat: 原时间的格式，如 FormatNormal （不支持 FormatSimpleWithMs）
// timeStr: 原时间的字符串
func FormatInLocalZone(oldFormat, timeStr string) (string, error){

	// 获取当前的时区
	loc, err := time.LoadLocation("Local")
	if err != nil{
		return timeStr, err
	}


	// 转换为标准时间对象
	t, err := time.ParseInLocation(oldFormat,timeStr, loc)
	if err != nil{
		return timeStr, err
	}

	// 转换到当前的时区
	t = t.In(loc)
	return t.Format( time.RFC3339 ), nil
}
