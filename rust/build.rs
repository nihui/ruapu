fn main() {
    cc::Build::new()
        .file("src/ruapu-binding.c")
        .compile("ruapu-rs");
    println!("cargo:rerun-if-changed=ruapu-binding.c");
}
