/*
  使用 channel 作为生成器，类似于python的 yeild 和 xrange
  https://studygolang.com/articles/9531
*/

package channel

import(
	"testing"
	"fmt"
)

func TestXrange(t *testing.T){
	generator := Xrange()

	for i := 0; i < 10; i++{
		fmt.Printf("%v\n", <-generator)
	}
}
