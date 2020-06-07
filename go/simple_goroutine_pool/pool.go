/*
   简单的 goroutine 池
   一个池子 Pool
   池子中有一个任务channel, work
   提交任务就是 往work中丢一个 Task
   池子启动后(New)，会启动多个 goroutine，不断从work中读取数据
*/

package simple_goroutine_pool

import (
	"sync"
)

type Task interface {
	Task()
}

type Pool struct {
	work chan Task
	wg   sync.WaitGroup
}

// Submit submit task
func (p *Pool) Submit(t Task) {
	p.work <- t
}

// Shutdown shutdown pool
func (p *Pool) Shutdown(){
	close(p.work)
}

func New(workers int) *Pool {
	pool := Pool{
		work: make(chan Task),
	}
	pool.wg.Add(workers)

	for i := 0; i < workers; i++ {
		go func() {
			defer pool.wg.Done()

			for t := range pool.work {
				t.Task()
			}
		}()
	}

	return &pool
}