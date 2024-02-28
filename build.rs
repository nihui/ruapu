fn main() {
    cc::Build::new()
        .file("ruapu-binding.c")
        .define("RUST_BINDING", "1")
        .compile("ruapu-rs");
    println!("cargo:rerun-if-changed=ruapu-binding.c");
}
