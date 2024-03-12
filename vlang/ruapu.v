module main

import ruapu

fn main() {
    ruapu.ruapu_init()
    mut avx2_status := ruapu.ruapu_supports('avx2')
    if avx2_status {
        println('avx2: ' + avx2_status.str())
    }

    println(ruapu.ruapu_rua())
}