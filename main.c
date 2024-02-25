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
    PRINT_ISA_SUPPORT(fma4)
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
    PRINT_ISA_SUPPORT(asimdrdm)
    PRINT_ISA_SUPPORT(asimdhp)
    PRINT_ISA_SUPPORT(asimddp)
    PRINT_ISA_SUPPORT(asimdfhm)
    PRINT_ISA_SUPPORT(bf16)
    PRINT_ISA_SUPPORT(i8mm)
    PRINT_ISA_SUPPORT(mte)
    PRINT_ISA_SUPPORT(sve)
    PRINT_ISA_SUPPORT(sve2)
    PRINT_ISA_SUPPORT(svebf16)
    PRINT_ISA_SUPPORT(svei8mm)
    PRINT_ISA_SUPPORT(svef32mm)
    PRINT_ISA_SUPPORT(pmull)
    PRINT_ISA_SUPPORT(crc32)
    PRINT_ISA_SUPPORT(aes)
    PRINT_ISA_SUPPORT(sha1)
    PRINT_ISA_SUPPORT(sha2)
    PRINT_ISA_SUPPORT(sha3)
    PRINT_ISA_SUPPORT(sha512)
    PRINT_ISA_SUPPORT(sm3)
    PRINT_ISA_SUPPORT(sm4)
    PRINT_ISA_SUPPORT(amx)

#elif __arm__ || defined(_M_ARM)
    PRINT_ISA_SUPPORT(edsp)
    PRINT_ISA_SUPPORT(neon)
    PRINT_ISA_SUPPORT(vfpv4)
    PRINT_ISA_SUPPORT(idiv)

#elif __mips__
    PRINT_ISA_SUPPORT(msa)

#elif __powerpc__
    PRINT_ISA_SUPPORT(vsx)

#elif __s390x__
    PRINT_ISA_SUPPORT(zvector)

#elif __loongarch__
    PRINT_ISA_SUPPORT(lsx)
    PRINT_ISA_SUPPORT(lasx)

#elif __riscv
    PRINT_ISA_SUPPORT(i)
    PRINT_ISA_SUPPORT(m)
    PRINT_ISA_SUPPORT(a)
    PRINT_ISA_SUPPORT(f)
    PRINT_ISA_SUPPORT(d)
    PRINT_ISA_SUPPORT(c)
    PRINT_ISA_SUPPORT(zfa)
    PRINT_ISA_SUPPORT(zfh)
    PRINT_ISA_SUPPORT(zfhmin)
    PRINT_ISA_SUPPORT(zicsr)
    PRINT_ISA_SUPPORT(zifencei)

#endif

    return 0;
}
