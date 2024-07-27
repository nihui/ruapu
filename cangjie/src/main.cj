import ruapu.*
main(): Int64 {
    ruapu_init()
    let neon_supported = ruapu_supports("neon")
    println("supports neon: ${neon_supported}") 
    let d = ruapu_rua()
    for (i in d) {
        println(i)
    }
    return 0
}