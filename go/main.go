package main

import (
	"fmt"
	"ruapu-go/ruapu"
	"strconv"
)

func main() {
	ruapu.Init()
	avx2Status := ruapu.Supports("avx2")
	fmt.Println("avx2:" + strconv.Itoa(avx2Status))
	rua := ruapu.Rua()
	fmt.Println(rua)
}
