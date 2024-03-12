module ruapu

#flag -I @VMODROOT/../
#flag -D RUAPU_IMPLEMENTATION
#include "ruapu.h"

fn C.ruapu_init()

fn C.ruapu_supports(&char) int

fn C.ruapu_rua() &&char

pub fn ruapu_init() {
    C.ruapu_init()
}

pub fn ruapu_supports(isa string) bool {
    return C.ruapu_supports(unsafe { isa.str }) == 1
}

pub fn ruapu_rua() []string {
    mut cstr_array := C.ruapu_rua()
    mut v_strings := []string{}
    
    unsafe {
        for i := 0; cstr_array[i] != 0; i++ {
            str :=  cstring_to_vstring(cstr_array[i])
            v_strings << str
        }
    }
    
    return v_strings
}
