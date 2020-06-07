package errorhandler

import "fmt"

type MyError struct {
	err    error
	pkg    string
	method string
	log    string
}

// checkError 检查是否发生错误，如果有错误，直接panic
func checkError(err error, pkg, method, log string) {
	if err != nil {
		panic(&MyError{
			err:    err,
			pkg:    pkg,
			method: method,
			log:    log,
		})
	}
}

// returnError 在defer中使用，捕获panic的错误
func returnError() {
	if me := recover(); me != nil {
		if e, ok := me.(*MyError); ok {
			fmt.Printf("%v|%v, %v, err:%v\n", e.pkg, e.method, e.log, e.err.Error())
		}
	}
}
