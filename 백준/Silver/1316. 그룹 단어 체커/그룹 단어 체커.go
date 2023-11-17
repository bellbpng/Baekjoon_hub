package main

import (
	"fmt"
	"bufio"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	var n int
	fmt.Scanf("%d", &n)
	ans := 0
	for test_case := 0; test_case < n; test_case++ {
		alpha := make([]bool, 26)
		str, _ := reader.ReadString('\n')
		flag := true
		// len() -> length of the string including null
		for j:=0; j<len(str)-2; j++ {
			if str[j] != str[j+1] {
				idx := str[j] - 'a'
				if alpha[idx]==true{
					flag = false
					break
				}
				alpha[idx] = true
			}
		}
		idx := str[len(str)-2] - 'a'
		if alpha[idx]==true { flag = false }
		if flag { ans++ }
	}
	fmt.Printf("%d\n", ans)
}