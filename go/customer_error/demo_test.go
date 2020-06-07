package customer_error

import(
	"testing"
	"fmt"
)

func TestErr(t *testing.T){

	e1 := MyError{msg:"my error"}
	fmt.Println(e1.Error())

	fmt.Println(DemoErrorTimeout.Error())
	fmt.Println(ErrInvalidParam.Error())
}