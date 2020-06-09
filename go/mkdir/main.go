package main

import (
	"os"
)

func main() {

	// os.Mkdir 只能创建Single Directory
	// os.MkdirAll 递归创建，会把路径中所有目录都创建

	if err := os.Mkdir("/tmp/dir1", os.ModePerm); err != nil {
		panic(err)
	}

	if err := os.MkdirAll("/tmp/dir1/dir2", os.ModePerm); err != nil {
		panic(err)
	}
}
