extern crate ruapu;

fn main() {
    println!("supports neon: {}", ruapu::supports("neon").unwrap());
    println!("supports avx2: {}", ruapu::supports("avx2").unwrap());
    println!("rua: {:?}", ruapu::rua());
}
