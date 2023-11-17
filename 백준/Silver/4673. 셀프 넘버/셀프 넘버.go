package main

import (
	"fmt"
)

var data[10001] int

func d(n int) int{
	ret := n
	tmp := n
	for tmp/10 != 0{
		ret += tmp%10
		tmp /= 10
	}
	ret += tmp%10
	return ret
}

func main(){
	for i:=1; i<=10000; i++ {
		data[i] = 1
	}

	var number int
	for i:=1; i<=10000; i++ {
		if data[i]==0 { continue }
		number = i
		for number <= 10000{
			number = d(number)
			if number>10000 { break }
			data[number] = 0
		}
	}

	for i:=1; i<=10000; i++ {
		if data[i]==1 {
			fmt.Printf("%d\n", i)
		}
	}
}