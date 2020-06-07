// GORM 的 使用示例
package main

import (
	"fmt"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
)

// 订单
type Order struct {
	ID     int64  `gorm:"column:id;primary_key"`  // 订单ID
	Name   string `gorm:"column:name;not null"`   // 订单名称
	Status int32  `gorm:"column:status;not null"` // 订单当前状态
}

func (Order) TableName() string {
	return "tbl_order"
}

// DemoGroupBy Select Group By 示例
// 统计每种状态的订单的总数
// select status, count(status) as cnt from tbl_order group by status
func DemoGroupBy(inst *gorm.DB) {
	type Result struct {
		Status int32  `gorm:"column:status"`
		Count  uint32 `gorm:"column:cnt"`
	}

	results := make([]Result, 0)
	if err := inst.Model(&Order{}).Select("status, count(status) as cnt").
		Group("status").Scan(&results).Error; err != nil {
		fmt.Printf("db err: %v", err.Error())
		return
	}

	for _, r := range results {
		fmt.Printf("%v \n", r)
	}
}

func main() {
	dialect := "mysql"
	args := "tencent:tencent@tcp(localhost)/cmp?charset=utf8&parseTime=True&loc=Local"
	db, err := gorm.Open(dialect, args)
	if err != nil {
		fmt.Println(err)
		return
	}

	if err := db.AutoMigrate(&Order{}).Error; err != nil {
		fmt.Println(err)
		return
	}

	DemoGroupBy(db)
}
