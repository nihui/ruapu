# ruapu
Detect cpu isa features with single-file

<table>
<tr><td>CPU</td><td> &#9989; x86, x86-64<br/>&#9989; arm, aarch64</td><td rowspan=3>
  
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

# Let's ruapu

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
