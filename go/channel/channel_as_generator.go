/*
  使用 channel 作为生成器，类似于python的 yeild 和 xrange
  https://studygolang.com/articles/9531
*/

package channel

// Xrange 返回一个generator, 调用一次该generator 就可以取到一次数
func Xrange() chan int {

	ch := make(chan int)  // 无缓存的channel

	go func(){
		for i := 0; ; i++ {
			ch <- i      // 关键：由于是无缓存的channel，所以这里会堵塞住，只有外面取数据之后，才会继续运行。
		}
	}()

	return ch
}