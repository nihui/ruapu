# ruapu

![GitHub License](https://img.shields.io/github/license/nihui/ruapu?style=for-the-badge)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/nihui/ruapu/ci.yml?style=for-the-badge)

Detect CPU ISA features with single-file

<table>
<tr><td>CPU</td><td>&#9989; x86, x86-64<br/>&#9989; arm, aarch64</td><td rowspan=3>
  
```c
#define RUAPU_IMPLEMENTATION
#include "ruapu.h"

int main()
{
    // initialize ruapu once
    ruapu_init();

    // now, tell me if this cpu has avx2
    int has_avx2 = ruapu_supports("avx2");

    return 0;
}
```

</td></tr>
<tr><td>OS</td><td>&#9989; Windows<br/>&#9989; Linux<br/>&#9989; macOS<br/>&#9989; Android<br/>&#9989; iOS</td></tr>
<tr><td>Compiler</td><td>&#9989; GCC<br/>&#9989; Clang<br/>&#9989; MSVC<br/>&#9989; MinGW</td></tr>
</table>

## Let's ruapu

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
|arm|`edsp` `neon` `vfpv4`|
|aarch64|`neon` `vfpv4` `cpuid` `asimdhp` `asimddp` `asimdfhm` `bf16` `i8mm` `sve` `sve2` `svebf16` `svei8mm` `svef32mm`|
|mips||
|powerpc||
|loongarch||
|risc-v||

## Techniques inside ruapu
ruapu is implemented in C language to ensure the widest possible portability.

ruapu determines whether the CPU supports certain instruction sets by trying to execute instructions and detecting whether an `Illegal Instruction` exception occurs. ruapu does not rely on the cpuid instructions and registers related to the CPU architecture, nor does it rely on the `MISA` information and system calls of the operating system. This can help us get more detailed CPU ISA information.

## License
MIT License
