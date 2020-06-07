package timeutil

import (
	"fmt"
	"testing"
)

func TestGetCurrentFormatedTime(t *testing.T){
	fmt.Println(GetCurrentFormatedTime(FormatNormal))
	fmt.Println(GetCurrentFormatedTime(FormatWithMs))
	fmt.Println(GetCurrentFormatedTime(FormatSimple))
	fmt.Println(GetCurrentFormatedTime(FormatSimpleWithMs))
	fmt.Println(GetCurrentFormatedTime(FormatSimpleWithMsDot))
	fmt.Println(FormatInLocalZone(FormatNormal, "2019-03-14 15:04:05"))
}


