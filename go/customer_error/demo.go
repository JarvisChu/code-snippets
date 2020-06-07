/*
  展示自定义错误的几种方式
*/

package customer_error

import(
	"errors"
)

// 方式1 实现 Error() string 接口
type MyError struct{
	msg string
}

func (e *MyError) Error() string{
	return e.msg
}


// 方式2 类似于redis.Nil
const DemoErrorTimeout = DemoError("timeout")
const DemoErrorInvalidParam = DemoError("invalid param")

type DemoError string
func (e DemoError) Error() string { return string(e) }

func ThrowError() error{
	return DemoErrorInvalidParam
}

// 方式3 使用var + errors
var ErrTimeout = errors.New("timeout")
var ErrInvalidParam = errors.New("invalid param")

