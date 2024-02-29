package ruapu

/*
#cgo CFLAGS: -I ../../
#define RUAPU_IMPLEMENTATION
#include "ruapu.h"
#include "stdlib.h"
*/
import "C"
import (
	"unsafe"
)

func Init() {
	C.ruapu_init()
}

func Supports(isa string) int {
	ptr := C.CString(isa)
	defer C.free(unsafe.Pointer(ptr))
	result := int(C.ruapu_supports(ptr))
	return result
}

func Rua() []string {
	p := unsafe.Pointer(C.ruapu_rua())
	s := make([]string, 0, 1)
	for i := 0; ; i++ {
		q := *(*unsafe.Pointer)(unsafe.Pointer(uintptr(p) + uintptr(i)*unsafe.Sizeof(p)))
		if q == nil {
			break
		}
		s = append(s, C.GoString((*C.char)(q)))
	}
	return s
}
