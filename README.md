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
<tr><td>OS</td><td>&#9989; Windows<br/>&#9989; Linux<br/>&#9989; macOS<br/>&#9989; Android<br/>&#9989; iOS<br/>&#9989; FreeBSD<br/>&#9989; NetBSD<br/>&#9989; OpenBSD</td></tr>
<tr><td>Compiler</td><td>&#9989; GCC<br/>&#9989; Clang<br/>&#9989; MSVC<br/>&#9989; MinGW</td></tr>
</table>

#### Best practice for using `ruapu.h` in multiple compilation units

1. Create one `ruapu.c` for your project
2. `ruapu.c` is **ONLY** `#define RUAPU_IMPLEMENTATION` and `#include "ruapu.h"`
3. Other sources `#include "ruapu.h"` but **NO** `#define RUAPU_IMPLEMENTATION`

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
pip3 install .
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
```
</td></tr>
</table>

<details>
<summary>Github-hosted runner result (Linux)</summary>

```
mmx = 1
sse = 1
sse2 = 1
sse3 = 1
ssse3 = 1
sse41 = 1
sse42 = 1
sse4a = 1
xop = 0
avx = 1
f16c = 1
fma = 1
avx2 = 1
avx512f = 0
avx512bw = 0
avx512cd = 0
avx512dq = 0
avx512vl = 0
avx512vnni = 0
avx512bf16 = 0
avx512ifma = 0
avx512vbmi = 0
avx512vbmi2 = 0
avx512fp16 = 0
avxvnni = 0
avxvnniint8 = 0
avxifma = 0
```

</details>

<details>
<summary>Github-hosted runner result (macOS)</summary>

```
mmx = 1
sse = 1
sse2 = 1
sse3 = 1
ssse3 = 1
sse41 = 1
sse42 = 1
sse4a = 0
xop = 0
avx = 1
f16c = 1
fma = 1
avx2 = 1
avx512f = 0
avx512bw = 0
avx512cd = 0
avx512dq = 0
avx512vl = 0
avx512vnni = 0
avx512bf16 = 0
avx512ifma = 0
avx512vbmi = 0
avx512vbmi2 = 0
avx512fp16 = 0
avxvnni = 0
avxvnniint8 = 0
avxifma = 0
```

</details>

<details>
<summary>Github-hosted runner result (macOS M1)</summary>

```
neon = 1
vfpv4 = 1
cpuid = 0
asimdhp = 1
asimddp = 1
asimdfhm = 1
bf16 = 0
i8mm = 0
sve = 0
sve2 = 0
svebf16 = 0
svei8mm = 0
svef32mm = 0
```

</details>

<details>
<summary>Github-hosted runner result (Windows)</summary>

```
mmx = 1
sse = 1
sse2 = 1
sse3 = 1
ssse3 = 1
sse41 = 1
sse42 = 1
sse4a = 1
xop = 0
avx = 1
f16c = 1
fma = 1
avx2 = 1
avx512f = 0
avx512bw = 0
avx512cd = 0
avx512dq = 0
avx512vl = 0
avx512vnni = 0
avx512bf16 = 0
avx512ifma = 0
avx512vbmi = 0
avx512vbmi2 = 0
avx512fp16 = 0
avxvnni = 0
avxvnniint8 = 0
avxifma = 0
```

</details>

<details>
<summary>FreeBSD/NetBSD/OpenBSD VM result (x86_64)</summary>

```
mmx = 1
sse = 1
sse2 = 1
sse3 = 1
ssse3 = 1
sse41 = 1
sse42 = 1
sse4a = 1
xop = 0
avx = 1
f16c = 1
fma = 1
fma4 = 0
avx2 = 1
avx512f = 0
avx512bw = 0
avx512cd = 0
avx512dq = 0
avx512vl = 0
avx512vnni = 0
avx512bf16 = 0
avx512ifma = 0
avx512vbmi = 0
avx512vbmi2 = 0
avx512fp16 = 0
avxvnni = 0
avxvnniint8 = 0
avxifma = 0
```

</details>


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
|x86|`mmx` `sse` `sse2` `sse3` `ssse3` `sse41` `sse42` `sse4a` `xop` `avx` `f16c` `fma` `fma4` `avx2` `avx512f` `avx512bw` `avx512cd` `avx512dq` `avx512vl` `avx512vnni` `avx512bf16` `avx512ifma` `avx512vbmi` `avx512vbmi2` `avx512fp16` `avxvnni` `avxvnniint8` `avxifma`|
|arm|`edsp` `neon` `vfpv4` `idiv`|
|aarch64|`neon` `vfpv4` `cpuid` `asimdrdm` `asimdhp` `asimddp` `asimdfhm` `bf16` `i8mm` `mte` `sve` `sve2` `svebf16` `svei8mm` `svef32mm` `pmull` `crc32` `aes` `sha1` `sha2` `sha3` `sha512` `sm3` `sm4` `amx`|
|mips|`msa`|
|powerpc|`vsx`|
|s390x|`zvector`|
|loongarch|`lsx` `lasx`|
|risc-v|`i` `m` `a` `f` `d` `c` `zfa` `zfh` `zfhmin` `zicsr` `zifencei` `zmmul` |
|openrisc| `orbis32` `orbis64` `orfpx32` `orfpx64` `orvdx64` |

## Techniques inside ruapu
ruapu is implemented in C language to ensure the widest possible portability.

ruapu determines whether the CPU supports certain instruction sets by trying to execute instructions and detecting whether an `Illegal Instruction` exception occurs. ruapu does not rely on the cpuid instructions and registers related to the CPU architecture, nor does it rely on the `MISA` information and system calls of the operating system. This can help us get more detailed CPU ISA information.

## FAQ
#### Why is the project named ruapu

&emsp;ruapu is the abbreviation of rua-cpu, which means using various extended instructions to harass and amuse the CPU (rua!). Based on whether the CPU reacts violently (throws an illegal instruction exception), it is inferred whether the CPU supports a certain extended instruction set.

#### Why is ruapu API designed like this

&emsp;We consider gcc builtin functions to be good practice, saying `__builtin_cpu_init()` and `__builtin_cpu_supports()`. ruapu refers to this design, which can be a 1:1 replacement for gcc functions, and supports more operating systems and compilers, giving it better portability.

#### Why does SIGILL occur when executing in debugger or simulator, such as `gdb`, `lldb`, `qemu-user`, `sde` etc.

&emsp;Because debuggers and simulators capture the signal and stop the ruapu signal handler function by default, we can continue execution at this time, or configure it specifically, such as `handle SIGILL nostop` in gdb. ruapu technically cannot prevent programs from stopping in debuggers and emulators

#### How to add detection capabilities for new instructions to ruapu

&emsp;_Assume that the new extended instruction set is named `rua`_

1. Add `RUAPU_INSTCODE(rua, rua-inst-hex) // rua r0,r0` and `RUAPU_ISAENTRY(rua)` in `ruapu.h`
2. Add `PRINT_ISA_SUPPORT(rua)` in `main.c` to print the detection result
3. Add entries about `rua` in README.md
4. Create a pull request!

&emsp;_https://godbolt.org/ is a good helper to view the compiled binary code of instructions._

## Repos that use ruapu
* [ncnn](https://github.com/Tencent/ncnn) &emsp;_High-performance neural network inference framework_
* [libllm](https://github.com/ling0322/libllm) &emsp;_Efficient inference of large language models_

## Credits
* [@nihui](https://github.com/nihui) &emsp;_Write the initial POC code and ruapu maintainer_
* [@kernelbin](https://github.com/kernelbin) &emsp;_Implement exception handling for Windows_
* [@zchrissirhcz](https://github.com/zchrissirhcz) &emsp;_Detect x86 FMA4_
* [@MollySophia](https://github.com/MollySophia) &emsp;_Fix C++ export symbol_
* [@strongtz](https://github.com/strongtz) &emsp;_Detect more aarch64 ISA_
* [@monkeyking](https://github.com/monkeyking) &emsp;_Detect apple arm64 AMX_
* [@junchao-loongson](https://github.com/junchao-loongson) &emsp;_Add loongarch support_
* [@ziyao233](https://github.com/ziyao233) &emsp;_Detect more risc-v ISA_
* [@dreamcmi](https://github.com/dreamcmi) &emsp;_Detect more risc-v ISA_
* [@cocoa-xu](https://github.com/cocoa-xu) &emsp;_Add FreeBSD support, python support_
* [@YuzukiTsuru](https://github.com/YuzukiTsuru) &emsp;_Add OpenRISC support_

## License
MIT License
