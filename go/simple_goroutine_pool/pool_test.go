package simple_goroutine_pool

import (
	"testing"
	"fmt"
	"time"
)

type Printing struct {
}

func (p *Printing) Task() {
	fmt.Println("printing")
	time.Sleep(time.Second)
}

func TestSimpleGoroutinePool(t *testing.T){
	poolSize := 2
	p := New(poolSize)

	tb := time.Now()
	for i := 0; i < 10; i++{
		p.Submit(&Printing{})
	}

	cost := int64(time.Now().Sub(tb) / time.Millisecond)
	fmt.Printf("cost:%v ms\n", cost)
}