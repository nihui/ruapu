// SPDX-License-Identifier: MIT
// Copyright (c) 2024 nihui (https://github.com/nihui)
// Copyright (c) 2024 kernelbin (https://github.com/kernelbin)
//
// ruapu --- detect cpu isa features with single-file

#include <stdio.h>

#define RUAPU_IMPLEMENTATION
#include "ruapu.h"

int main()
{
    ruapu_init();

#define PRINT_ISA_SUPPORT(isa) fprintf(stderr, "%s = %d\n", #isa, ruapu_supports(#isa));

#if defined(__i386__) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_X64)
    PRINT_ISA_SUPPORT(mmx)
    PRINT_ISA_SUPPORT(sse)
    PRINT_ISA_SUPPORT(sse2)
    PRINT_ISA_SUPPORT(sse3)
    PRINT_ISA_SUPPORT(ssse3)
    PRINT_ISA_SUPPORT(sse41)
    PRINT_ISA_SUPPORT(sse42)
    PRINT_ISA_SUPPORT(sse4a)
    PRINT_ISA_SUPPORT(xop)
    PRINT_ISA_SUPPORT(avx)
    PRINT_ISA_SUPPORT(f16c)
    PRINT_ISA_SUPPORT(fma)
    PRINT_ISA_SUPPORT(avx2)
    PRINT_ISA_SUPPORT(avx512f)
    PRINT_ISA_SUPPORT(avx512bw)
    PRINT_ISA_SUPPORT(avx512cd)
    PRINT_ISA_SUPPORT(avx512dq)
    PRINT_ISA_SUPPORT(avx512vl)
    PRINT_ISA_SUPPORT(avx512vnni)
    PRINT_ISA_SUPPORT(avx512bf16)
    PRINT_ISA_SUPPORT(avx512ifma)
    PRINT_ISA_SUPPORT(avx512vbmi)
    PRINT_ISA_SUPPORT(avx512vbmi2)
    PRINT_ISA_SUPPORT(avx512fp16)
    PRINT_ISA_SUPPORT(avxvnni)
    PRINT_ISA_SUPPORT(avxvnniint8)
    PRINT_ISA_SUPPORT(avxifma)

#elif __aarch64__ || defined(_M_ARM64)
    PRINT_ISA_SUPPORT(neon)
    PRINT_ISA_SUPPORT(vfpv4)
    PRINT_ISA_SUPPORT(cpuid)
    PRINT_ISA_SUPPORT(asimdhp)
    PRINT_ISA_SUPPORT(asimddp)
    PRINT_ISA_SUPPORT(asimdfhm)
    PRINT_ISA_SUPPORT(bf16)
    PRINT_ISA_SUPPORT(i8mm)
    PRINT_ISA_SUPPORT(sve)
    PRINT_ISA_SUPPORT(sve2)
    PRINT_ISA_SUPPORT(svebf16)
    PRINT_ISA_SUPPORT(svei8mm)
    PRINT_ISA_SUPPORT(svef32mm)

#elif __arm__ || defined(_M_ARM)
    PRINT_ISA_SUPPORT(edsp)
    PRINT_ISA_SUPPORT(neon)
    PRINT_ISA_SUPPORT(vfpv4)

#endif

    return 0;
}
