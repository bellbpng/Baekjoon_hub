package main

import (
	"fmt"
)

func main(){
	var arr[9] int
	for i:=0; i<9; i++ {
		fmt.Scanf("%d", &arr[i])
	}
	max := arr[0]
	max_idx := 0
	for i:=0; i<9; i++ {
		if max < arr[i] {
			max = arr[i]
			max_idx = i
		}
	}
	fmt.Printf("%d\n%d\n", max, max_idx+1)
}