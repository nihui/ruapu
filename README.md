# ruapu

![GitHub License](https://img.shields.io/github/license/nihui/ruapu?style=for-the-badge)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/nihui/ruapu/ci.yml?style=for-the-badge)

Detect CPU ISA features with single-file

<table>
<tr><td>CPU</td><td>&#9989; x86, x86-64<br/>&#9989; arm, aarch64<br/>&#9989; mips<br/>&#9989; powerpc<br/>&#9989; s390x<br/>&#9989; loongarch<br/>&#9989; risc-v<br/>&#9989; openrisc</td><td rowspan=3>

```c
#define RUAPU_IMPLEMENTATION
#include "ruapu.h"

int main()
{
    // initialize ruapu once
    ruapu_init();

    // now, tell me if this cpu has avx2
    int has_avx2 = ruapu_supports("avx2");

    // loop all supported features
    const char* const* supported = ruapu_rua();
    while (*supported)
    {
        fprintf(stderr, "%s\n", *supported);
        supported++;
    }

    return 0;
}
```

</td></tr>
<tr><td>OS</td><td>&#9989; Windows<br/>&#9989; Linux<br/>&#9989; macOS<br/>&#9989; Android<br/>&#9989; iOS<br/>&#9989; FreeBSD<br/>&#9989; NetBSD<br/>&#9989; OpenBSD<br/>&#9989; DragonflyBSD<br/>&#9989; Solaris<br/>&#9989; SyterKit</td></tr>
<tr><td>Compiler</td><td>&#9989; GCC<br/>&#9989; Clang<br/>&#9989; MSVC<br/>&#9989; MinGW</td></tr>
</table>

#### Best practice for using `ruapu.h` in multiple compilation units

1. Create one `ruapu.c` for your project
2. `ruapu.c` is **ONLY** `#define RUAPU_IMPLEMENTATION` and `#include "ruapu.h"`
3. Other sources `#include "ruapu.h"` but **NO** `#define RUAPU_IMPLEMENTATION`

## Features

* Detect **CPU ISA with single-file**&emsp;&emsp;&emsp;
  _`sse2`, `avx`, `avx512f`, `neon`, etc._
* Detect **vendor extended ISA**&emsp;&emsp;&emsp;&emsp;
  _apple `amx`, risc-v vendor ISA, etc._
* Detect **richer ISA on Windows ARM**&emsp;&emsp;
  _`IsProcessorFeaturePresent()` returns little ISA information_
* Detect **`x86-avx512` on macOS correctly**&emsp;
  _macOS hides it in `cpuid`_
* Detect **new CPU's ISA on old systems**&emsp;
  _they are usually not exposed in `auxv` or `MISA`_
* Detect **CPU hidden ISA**&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;
  _`fma4` on zen1, ISA in hypervisor, etc._

## Supported ISA _&emsp;(more is comming ... :)_

|CPU|ISA|
|:---:|---|
|x86|`mmx` `sse` `sse2` `sse3` `ssse3` `sse41` `sse42` `sse4a` `popcnt` `xop` `avx` `f16c` `fma` `fma4` `avx2` `avx512f` `avx512bw` `avx512cd` `avx512dq` `avx512vl` `avx512vnni` `avx512bf16` `avx512ifma` `avx512vbmi` `avx512vbmi2` `avx512fp16` `avx512er` `avx5124fmaps` `avx5124vnniw` `avxvnni` `avxvnniint8` `avxvnniint16` `avxifma` `avxneconvert` `amxfp16` `amxbf16` `amxint8` `amxtile` `bmi1` `bmi2` `gfni` `aesni` `vaes` `sha1` `sha256` `sha512` `sm3` `sm4` `rdrand` `rdseed` `tsx`|
|arm|`half` `edsp` `neon` `vfpv4` `idiv`|
|aarch64|`neon` `vfpv4` `lse` `cpuid` `asimdrdm` `asimdhp` `asimddp` `asimdfhm` `bf16` `i8mm` `frint` `jscvt` `fcma` `mte` `mte2` `sve` `sve2` `sve2p1` `svebf16` `svei8mm` `svef32mm` `svef64mm` `sme` `smef16f16` `smef64f64` `smei64i64` `pmull` `crc32` `aes` `sha1` `sha2` `sha3` `sha512` `sm3` `sm4` `svepmull` `svebitperm` `sveaes` `svesha3` `svesm4` `amx` `paca` `pacg`|
|mips|`msa` `mxu` `mxu2` `mxu3` `mmi` `sx` `asx` `msa2` `crypto`|
|powerpc|`altivec` `vsx`|
|s390x|`zvector`|
|loongarch|`lsx` `lasx`|
|risc-v|`i` `m` `a` `f` `d` `c` `p` `v` `zawrs` `zba` `zbb` `zbc` `zbpbo` `zbs` `zbkb` `zbkc` `zbkx` `zcb` `zfa` `zfbfmin` `zfh` `zfhmin` `zicbop` `zicbom` `zicond` `zicsr` `zifencei` `zihintpause` `zmmul` `zpn` `zpsfoperand` `zvbb` `zvbc` `zvfh` `zvfhmin` `zvfbfmin` `zvfbfwma` `zvkb` `zvkg` `zvkned` `zvknha` `zvknhb` `zvksed` `zvksh` `zvl32b` `zvl64b` `zvl128b` `zvl256b` `zvl512b` `zvl1024b` `xsfvfnrclipxfqf` `xsfvfwmaccqqq` `xsfvqmaccdod` `xsfvqmaccqoq` `xtheadba` `xtheadbb` `xtheadbs` `xtheadcondmov` `xtheadfmemidx` `xtheadfmv` `xtheadmac` `xtheadmemidx` `xtheadmempair` `xtheadsync` `xtheadvector` `xtheadvdot` `xsmtvmadoti8` `xsmtvmadoti4` `xsmtvmadotni8` `xsmtvfmadotf32` `xsmtvfwmadotf16` `xsmtvmadothpi8` `xsmtvmadothpi4` `xsmtvpack` `xsmtvnspack`|
|openrisc| `orbis32` `orbis64` `orfpx32` `orfpx64` `orvdx64` |

## Let's ruapu

### ruapu with C

<table>

<tr><td>

Compile ruapu test program

```shell
# GCC / MinGW
gcc main.c -o ruapu
```
```shell
# Clang
clang main.c -o ruapu
```
```shell
# MSVC
cl.exe /Fe: ruapu.exe main.c
```
</td>
<td>

Run ruapu in command line

```shell
./ruapu
mmx = 1
sse = 1
sse2 = 1
sse3 = 1
ssse3 = 1
sse41 = 1
sse42 = 1
sse4a = 1
xop = 0
... more lines omitted ...
```

</td></tr>
</table>

### ruapu with Python

<table>

<tr><td>

Compile and install ruapu library

```shell
# from pypi
pip3 install ruapu
```

```shell
# from source code
pip3 install ./python
```
</td>
<td>

Use ruapu in python

```python
import ruapu

ruapu.supports("avx2")
# True

ruapu.supports(isa="avx2")
# True

ruapu.rua()
#(mmx', 'sse', 'sse2', 'sse3', 'ssse3', 'sse41', 'sse42', 'avx', 'f16c', 'fma', 'avx2')
```
</td></tr>
</table>

### ruapu with Rust

<table>

<tr><td>

Compile ruapu library

```shell
# from source code
cd rust
cargo build --release
```
</td>
<td>

Use ruapu in Rust

```rust
extern crate ruapu;

fn main() {
    println!("supports neon: {}", ruapu::supports("neon").unwrap());
    println!("supports avx2: {}", ruapu::supports("avx2").unwrap());
    println!("rua: {:?}", ruapu::rua());
}
```
</td></tr>
</table>

### ruapu with Lua

<table>

<tr><td>

Compile ruapu library

```shell
# from source code
cd lua
# lua binding has been tested on Lua 5.2~5.4
luarocks make
```
</td>
<td>

Use ruapu in Lua

```Lua
ruapu = require "ruapu";
print(ruapu.supports("mmx"));
for _, ext in ipairs(ruapu.rua()) do
    print(ext);
end
```
</td></tr>
</table>

### ruapu with Erlang

<table>

<tr><td>

Compile ruapu library

```erlang
% add this to deps list 
% in your rebar.config
{ruapu, "0.1.0"}
```
</td>
<td>

Use ruapu in Erlang `rebar3 shell`

```erlang
ruapu:rua().
{ok,["neon","vfpv4","asimdrdm","asimdhp","asimddp",
     "asimdfhm","bf16","i8mm","pmull","crc32","aes","sha1",
     "sha2","sha3","sha512","amx"]}
> ruapu:supports("neon").
true
> ruapu:supports(neon).
true
> ruapu:supports(<<"neon">>).
true
> ruapu:supports("avx2").
false
> ruapu:supports(avx2).
false
> ruapu:supports(<<"avx2">>).
false
```

</td></tr>
</table>

### ruapu with Fortran

<table>

<tr><td>

Compile ruapu library

```shell
# from source code
cd fortran
cmake -B build
cmake --build build
```
</td>
<td>

Use ruapu in Fortran

```fortran
program main
    use ruapu, only: ruapu_init, ruapu_supports, ruapu_rua
    implicit none

    character(len=:), allocatable :: isa_supported(:)
    integer :: i

    call ruapu_init()

    print *, "supports sse: ", ruapu_supports("sse")
    print *, "supports neon: ", ruapu_supports("neon")

    isa_supported = ruapu_rua()
    do i = 1, size(isa_supported)
        print *, trim(isa_supported(i))
    end do
end program main

```
</td></tr>
</table>

### ruapu with Golang

<table>


<tr><td>

Compile ruapu library

```shell
cd go
go build -o ruapu-go
```

</td>
<td>

Use ruapu in Golang

```go
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
```

</td></tr>
</table>

### ruapu with Haskell

<table>
<tr><td>

Add ruapu library to your project

`haskell/Ruapu.hs`, `haskell/ruapu.c` and `ruapu.h` should be copied in your
project.

</td>
<td>

Use ruapu in Haskell

```haskell
import Ruapu
-- Ruapu.rua :: IO [String]
-- Ruapu.supports :: String -> IO Bool
main = do
    Ruapu.init
    Ruapu.supports "mmx" >>= putStrLn . show
    Ruapu.rua >>= sequence_ . map putStrLn
```
</td></tr>
</table>

### ruapu with Vlang

<table>


<tr><td>

Compile ruapu library

```shell
cd vlang
v .
```

</td>
<td>

Use ruapu in Vlang

```go
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
```

</td></tr>
</table>

### ruapu with Pascal

<table>

<tr><td>

Compile ruapu library

```shell
cd pascal
sudo apt install fpc
cmake .
make
fpc ruapu.lpr
```

</td>
<td>

Use ruapu in Pascal

```pascal
program ruapu;

uses ruapu_pascal;

var
  has_avx2: integer;
  supported: PPAnsiChar;
begin
  // initialize ruapu once
  ruapu_init();

  // now, tell me if this cpu has avx2
  has_avx2 := ruapu_supports('avx2');

  // loop all supported features
  supported := ruapu_rua();
  while supported^ <> nil do
  begin
      writeln(supported^);
      inc(supported);
  end;

  readln();
end.
      
```

</td></tr>
</table>

### ruapu with Java

<table>

<tr><td>

Compile ruapu library and example

```shell
./gradlew build
```
Run example
```shell
java -cp \
    ./build/libs/ruapu-1.0-SNAPSHOT.jar \
    ./Example.java
```

</td>
<td>


Use ruapu in Java

```java
import ruapu.Ruapu;
import java.util.*;

class Example {
    public static void main(String args[]) {
        Ruapu ruapu = new Ruapu();
        
        System.out.println("avx: " + ruapu.supports("avx")); 
        // avx: 1
        System.out.println(Arrays.toString(ruapu.rua())); 
        // [mmx, sse, sse2, sse3, ssse3, sse41, sse42, avx, f16c, fma, avx2]
    }
}
      
```




</td></tr>
</table>
