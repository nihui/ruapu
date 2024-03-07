// SPDX-License-Identifier: MIT
// Copyright (c) 2024 nihui (https://github.com/nihui)
// Copyright (c) 2024 kernelbin (https://github.com/kernelbin)
//
// ruapu --- detect cpu isa features with single-file

#ifndef RUAPU_H
#define RUAPU_H

#ifdef __cplusplus
extern "C" {
#endif

void ruapu_init();

int ruapu_supports(const char* isa);

const char* const* ruapu_rua();

#ifdef RUAPU_IMPLEMENTATION

#if defined _WIN32

#include <windows.h>
#include <setjmp.h>
#include <string.h>

#if WINAPI_FAMILY == WINAPI_FAMILY_APP
// uwp does not support veh  :(
#if defined (_MSC_VER)
#pragma message("warning: ruapu does not support UWP yet.")
#else
#warning ruapu does not support UWP yet.
#endif
static int ruapu_detect_isa(const void* some_inst)
{
    (void)some_inst;
    return 0;
}
#else // WINAPI_FAMILY == WINAPI_FAMILY_APP
static int g_ruapu_sigill_caught = 0;
static jmp_buf g_ruapu_jmpbuf;

typedef const void* ruapu_some_inst;

static LONG CALLBACK ruapu_catch_sigill(struct _EXCEPTION_POINTERS* ExceptionInfo)
{
    if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_ILLEGAL_INSTRUCTION)
    {
        g_ruapu_sigill_caught = 1;
        longjmp(g_ruapu_jmpbuf, -1);
    }

    return EXCEPTION_CONTINUE_SEARCH;
}

static int ruapu_detect_isa(const void* some_inst)
{
    g_ruapu_sigill_caught = 0;

    PVOID eh = AddVectoredExceptionHandler(1, ruapu_catch_sigill);

    if (setjmp(g_ruapu_jmpbuf) == 0)
    {
        ((void (*)())some_inst)();
    }

    RemoveVectoredExceptionHandler(eh);

    return g_ruapu_sigill_caught ? 0 : 1;
}
#endif // WINAPI_FAMILY == WINAPI_FAMILY_APP

#elif defined __ANDROID__ || defined __linux__ || defined __APPLE__ || defined __FreeBSD__ || defined __NetBSD__ || defined __OpenBSD__ || defined __DragonFly__ || defined __sun__
#include <signal.h>
#include <setjmp.h>
#include <string.h>

static int g_ruapu_sigill_caught = 0;
static sigjmp_buf g_ruapu_jmpbuf;

typedef void (*ruapu_some_inst)();

static void ruapu_catch_sigill(int signo, siginfo_t* si, void* data)
{
    (void)signo;
    (void)si;
    (void)data;

    g_ruapu_sigill_caught = 1;
    siglongjmp(g_ruapu_jmpbuf, -1);
}

static int ruapu_detect_isa(ruapu_some_inst some_inst)
{
    g_ruapu_sigill_caught = 0;

    struct sigaction sa = { 0 };
    struct sigaction old_sa;
    sa.sa_flags = SA_ONSTACK | SA_RESTART | SA_SIGINFO;
    sa.sa_sigaction = ruapu_catch_sigill;
    sigaction(SIGILL, &sa, &old_sa);

    if (sigsetjmp(g_ruapu_jmpbuf, 1) == 0)
    {
        some_inst();
    }

    sigaction(SIGILL, &old_sa, NULL);

    return g_ruapu_sigill_caught ? 0 : 1;
}

#elif defined __SYTERKIT__ 

typedef void (*ruapu_some_inst)();
#include <mmu.h>

static int g_ruapu_sigill_caught = 0;

void arm32_do_undefined_instruction(struct arm_regs_t *regs)
{
    g_ruapu_sigill_caught = 1;
    regs->pc += 4;
}

static int ruapu_detect_isa(ruapu_some_inst some_inst)
{
    g_ruapu_sigill_caught = 0;
    some_inst();
    return g_ruapu_sigill_caught ? 0 : 1;
}

#endif // defined _WIN32 || defined __ANDROID__ || defined __linux__ || defined __APPLE__ || defined __FreeBSD__ || defined __NetBSD__ || defined __OpenBSD__ || defined __DragonFly__ || defined __sun__ || defined __SYTERKIT__

#if defined _WIN32

#if defined(__i386__) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_X64)
#ifdef _MSC_VER
#define RUAPU_INSTCODE(isa, ...) __pragma(section(".text")) __declspec(allocate(".text")) static unsigned char ruapu_some_##isa[] = { __VA_ARGS__, 0xc3 };
#else
#define RUAPU_INSTCODE(isa, ...) __attribute__((section(".text"))) static unsigned char ruapu_some_##isa[] = { __VA_ARGS__, 0xc3 };
#endif

#elif __aarch64__ || defined(_M_ARM64)
#ifdef _MSC_VER
#define RUAPU_INSTCODE(isa, ...) __pragma(section(".text")) __declspec(allocate(".text")) static unsigned int ruapu_some_##isa[] = { __VA_ARGS__, 0xd65f03c0 };
#else
#define RUAPU_INSTCODE(isa, ...) __attribute__((section(".text"))) static unsigned int ruapu_some_##isa[] = { __VA_ARGS__, 0xd65f03c0 };
#endif

#elif __arm__ || defined(_M_ARM)
#if __thumb__
#ifdef _MSC_VER
#define RUAPU_INSTCODE(isa, ...) __pragma(section(".text")) __declspec(allocate(".text")) static unsigned short ruapu_some_##isa[] = { __VA_ARGS__, 0x4770 };
#else
#define RUAPU_INSTCODE(isa, ...) __attribute__((section(".text"))) static unsigned short ruapu_some_##isa[] = { __VA_ARGS__, 0x4770 };
#endif
#else
#ifdef _MSC_VER
#define RUAPU_INSTCODE(isa, ...) __pragma(section(".text")) __declspec(allocate(".text")) static unsigned int ruapu_some_##isa[] = { __VA_ARGS__, 0xe12fff1e };
#else
#define RUAPU_INSTCODE(isa, ...) __attribute__((section(".text"))) static unsigned int ruapu_some_##isa[] = { __VA_ARGS__, 0xe12fff1e };
#endif
#endif

#endif

#else // defined _WIN32

#if defined(__i386__) || defined(__x86_64__) || __s390x__
#define RUAPU_INSTCODE(isa, ...) static void ruapu_some_##isa() { asm volatile(".byte " #__VA_ARGS__ : : : ); }
#elif __aarch64__ || __arm__ || __mips__ || __riscv || __loongarch__
#if __thumb__
#define RUAPU_INSTCODE(isa, ...) static void ruapu_some_##isa() { asm volatile(".short " #__VA_ARGS__ : : : ); }
#else
#define RUAPU_INSTCODE(isa, ...) static void ruapu_some_##isa() { asm volatile(".word " #__VA_ARGS__ : : : ); }
#endif
#elif __powerpc__
#define RUAPU_INSTCODE(isa, ...) static void ruapu_some_##isa() { asm volatile(".long " #__VA_ARGS__ : : : ); }
#endif

#endif // defined _WIN32

#if defined(__i386__) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_X64)
RUAPU_INSTCODE(mmx, 0x0f, 0xdb, 0xc0) // pand mm0,mm0
RUAPU_INSTCODE(sse, 0x0f, 0x54, 0xc0) // andps xmm0,xmm0
RUAPU_INSTCODE(sse2, 0x66, 0x0f, 0xfe, 0xc0) // paddd xmm0,xmm0
RUAPU_INSTCODE(sse3, 0xf2, 0x0f, 0x7c, 0xc0) // haddps xmm0,xmm0
RUAPU_INSTCODE(ssse3, 0x66, 0x0f, 0x38, 0x06, 0xc0) // phsubd xmm0,xmm0
RUAPU_INSTCODE(sse41, 0x66, 0x0f, 0x38, 0x3d, 0xc0) // pmaxsd xmm0,xmm0
RUAPU_INSTCODE(sse42, 0x66, 0x0f, 0x38, 0x37, 0xc0) // pcmpgtq xmm0,xmm0
RUAPU_INSTCODE(sse4a, 0x66, 0x0f, 0x79, 0xc0) // extrq xmm0,xmm0
RUAPU_INSTCODE(xop, 0x8f, 0xe8, 0x78, 0xb6, 0xc0, 0x00)  // vpmadcswd xmm0,xmm0,xmm0,xmm0
RUAPU_INSTCODE(avx, 0xc5, 0xfc, 0x54, 0xc0) // vandps ymm0,ymm0,ymm0
RUAPU_INSTCODE(f16c, 0xc4, 0xe2, 0x7d, 0x13, 0xc0) // vcvtph2ps ymm0,xmm0
RUAPU_INSTCODE(fma, 0xc4, 0xe2, 0x7d, 0x98, 0xc0) // vfmadd132ps ymm0,ymm0,ymm0
RUAPU_INSTCODE(fma4, 0xc4, 0xe3, 0xfd, 0x68, 0xc0, 0x00) // vfmaddps ymm0,ymm0,ymm0,ymm0
RUAPU_INSTCODE(avx2, 0xc5, 0xfd, 0xfe, 0xc0) // vpaddd ymm0,ymm0,ymm0
RUAPU_INSTCODE(avx512f, 0x62, 0xf1, 0x7c, 0x48, 0x58, 0xc0) // vaddps zmm0,zmm0,zmm0
RUAPU_INSTCODE(avx512bw, 0x62, 0xf1, 0x7d, 0x48, 0xfd, 0xc0) // vpaddw zmm0,zmm0,zmm0
RUAPU_INSTCODE(avx512cd, 0x62, 0xf2, 0xfd, 0x48, 0x44, 0xc0) // vplzcntq zmm0,zmm0
RUAPU_INSTCODE(avx512dq, 0x62, 0xf1, 0x7c, 0x48, 0x54, 0xc0) // vandps zmm0,zmm0,zmm0
RUAPU_INSTCODE(avx512vl, 0x62, 0xf2, 0xfd, 0x28, 0x1f, 0xc0) // vpabsq ymm0,ymm0
RUAPU_INSTCODE(avx512vnni, 0x62, 0xf2, 0x7d, 0x48, 0x52, 0xc0) // vpdpwssd zmm0,zmm0,zmm0
RUAPU_INSTCODE(avx512bf16, 0x62, 0xf2, 0x7e, 0x48, 0x52, 0xc0) // vdpbf16ps zmm0,zmm0,zmm0
RUAPU_INSTCODE(avx512ifma, 0x62, 0xf2, 0xfd, 0x48, 0xb4, 0xc0) // vpmadd52luq zmm0,zmm0,zmm0
RUAPU_INSTCODE(avx512vbmi, 0x62, 0xf2, 0x7d, 0x48, 0x75, 0xc0) // vpermi2b zmm0,zmm0,zmm0
RUAPU_INSTCODE(avx512vbmi2, 0x62, 0xf2, 0x7d, 0x48, 0x71, 0xc0) // vpshldvd zmm0,zmm0,zmm0
RUAPU_INSTCODE(avx512fp16, 0x62, 0xf6, 0x7d, 0x48, 0x98, 0xc0) // vfmadd132ph zmm0,zmm0,zmm0
// TODO:avx512pf, vgatherpf1dps DWORD PTR [esp+zmm0*1]{k1}
RUAPU_INSTCODE(avx512er, 0x62, 0xf2, 0xfd, 0x48, 0xc8, 0xc0) //vexp2pd zmm0,zmm0
RUAPU_INSTCODE(avx5124fmaps, 0x67, 0x62, 0xf2, 0x7f, 0x48, 0x9a, 0x04, 0x24) //v4fmaddps zmm0,zmm0,XMMWORD PTR [esp]
RUAPU_INSTCODE(avx5124vnniw, 0x67, 0x62, 0xf2, 0x7f, 0x48, 0x52, 0x04, 0x24) //vp4dpwssd zmm0,zmm0,XMMWORD PTR [esp]
RUAPU_INSTCODE(avxvnni, 0xc4, 0xe2, 0x7d, 0x52, 0xc0) // vpdpwssd ymm0,ymm0,ymm0
RUAPU_INSTCODE(avxvnniint8, 0xc4, 0xe2, 0x7f, 0x50, 0xc0) // vpdpbssd ymm0,ymm0,ymm0
RUAPU_INSTCODE(avxvnniint16, 0xc4, 0xe2, 0x7e, 0xd2, 0xc0) // vpdpwsud ymm0,ymm0,ymm0
RUAPU_INSTCODE(avxifma, 0xc4, 0xe2, 0xfd, 0xb4, 0xc0) // vpmadd52luq ymm0,ymm0,ymm0
RUAPU_INSTCODE(amxfp16, 0xc4, 0xe2, 0x7b, 0x5c, 0xd1) // tdpfp16ps %tmm0, %tmm1, %tmm2
RUAPU_INSTCODE(amxbf16, 0xc4, 0xe2, 0x7a, 0x5c, 0xd1) // tdpbf16ps %tmm0, %tmm1, %tmm2
RUAPU_INSTCODE(amxint8, 0xc4, 0xe2, 0x7b, 0x5e, 0xd1) // tdpbssd %tmm0, %tmm1, %tmm2
RUAPU_INSTCODE(amxtile, 0xc4, 0xe2, 0x7a, 0x49, 0xc0) // tilezero %tmm0

#elif __aarch64__ || defined(_M_ARM64)
RUAPU_INSTCODE(neon, 0x4e20d400) // fadd v0.4s,v0.4s,v0.4s
RUAPU_INSTCODE(vfpv4, 0x1f000000) // fmadd s0,s0,s0,s0
RUAPU_INSTCODE(cpuid, 0xd5380000) // mrs x0,midr_el1
RUAPU_INSTCODE(asimdrdm, 0x6e808400) // sqrdmlah v0.4s,v0.4s,v0.4s
RUAPU_INSTCODE(asimdhp, 0x0e401400) // fadd v0.4h,v0.4h,v0.4h
RUAPU_INSTCODE(asimddp, 0x4e809400) // sdot v0.4h,v0.16b,v0.16b
RUAPU_INSTCODE(asimdfhm, 0x4e20ec00) // fmlal v0.4s,v0.4h,v0.4h
RUAPU_INSTCODE(bf16, 0x6e40ec00) // bfmmla v0.4h,v0.8h,v0.8h
RUAPU_INSTCODE(i8mm, 0x4e80a400) // smmla v0.4h,v0.16b,v0.16b
RUAPU_INSTCODE(mte, 0xd96003e0) // ldg x0,[sp]
RUAPU_INSTCODE(sve, 0x65608000) // fmad z0.h,p0/m,z0.h,z0.h
RUAPU_INSTCODE(sve2, 0x44405000) // smlslb z0.h,z0.b,z0.b
RUAPU_INSTCODE(svebf16, 0x6460e400) // bfmmla z0.s,z0.h,z0.h
RUAPU_INSTCODE(svei8mm, 0x45009800) // smmla z0.s,z0.b,z0.b
RUAPU_INSTCODE(svef32mm, 0x64a0e400) // fmmla z0.s,z0.s,z0.s
RUAPU_INSTCODE(pmull, 0x0e20e000) // pmull v0.8h,v0.8b,v0.8b
RUAPU_INSTCODE(crc32, 0x1ac04000) // crc32b w0,w0,w0
RUAPU_INSTCODE(aes, 0x4e285800) // aesd v0.16b,v0.16b
RUAPU_INSTCODE(sha1, 0x5e280800) // sha1h s0,s0
RUAPU_INSTCODE(sha2, 0x5e004000) // sha256h q0,q0,v0.4s
RUAPU_INSTCODE(sha3, 0xce000000) // eor3 v0.16b, v0.16b, v0.16b, v0.16b
RUAPU_INSTCODE(sha512, 0xce608000) // sha512h q0, q0, v0.2d
RUAPU_INSTCODE(sm3, 0xce60c000) // sm3partw1 v0.4s, v0.4s, v0.4s
RUAPU_INSTCODE(sm4, 0xcec08400) // sm4e v0.4s, v0.4s
RUAPU_INSTCODE(amx, 0x00201220) // amx setup


#elif __arm__ || defined(_M_ARM)
#if __thumb__
RUAPU_INSTCODE(half, 0xf8bd, 0x0000) // ldrh r0,[sp]
RUAPU_INSTCODE(edsp, 0xfb20, 0x0000) // smlad r0,r0,r0,r0
RUAPU_INSTCODE(neon, 0xef00, 0x0d40) // vadd.f32 q0,q0,q0
RUAPU_INSTCODE(vfpv4, 0xeea0, 0x0a00) // vfma.f32 s0,s0,s0
RUAPU_INSTCODE(idiv, 0x2003, 0xfb90, 0xf0f0) // movs r0,#3 + sdiv r0,r0,r0
#else
RUAPU_INSTCODE(half, 0xe1dd00b0) // ldrh r0,[sp]
RUAPU_INSTCODE(edsp, 0xe7000010) // smlad r0,r0,r0,r0
RUAPU_INSTCODE(neon, 0xf2000d40) // vadd.f32 q0,q0,q0
RUAPU_INSTCODE(vfpv4, 0xeea00a00) // vfma.f32 s0,s0,s0
RUAPU_INSTCODE(idiv, 0xe3a00003, 0xe710f010) // movs r0,#3 + sdiv r0,r0,r0
#endif

#elif __mips__
RUAPU_INSTCODE(msa, 0x7900001b) // fmadd.w $w0,$w0,$w0

#elif __powerpc__
RUAPU_INSTCODE(vsx, 0x104210c0) // vaddudm v2,v2,v2

#elif __s390x__
RUAPU_INSTCODE(zvector, 0xe7, 0x11, 0x12, 0x00, 0x10, 0x8f) // vfmasb v1,v1,v1,v1

#elif __loongarch__
RUAPU_INSTCODE(lsx, 0x700b0000) //vadd.w vr0, vr0, vr0
RUAPU_INSTCODE(lasx, 0x740b0000) //xvadd.w xr0, xr0, xr0

#elif __riscv
RUAPU_INSTCODE(i, 0x00a50533) // add a0,a0,a0
RUAPU_INSTCODE(m, 0x00200513, 0x02a50533, 0x02a54533) // addi a0,x0,2 mul a0,a0,a0 div a0,a0,a0
RUAPU_INSTCODE(a, 0x100122af, 0x185122af) // lr.w t0,(sp) + sc.w t0,t0,(sp)
RUAPU_INSTCODE(f, 0x10a57553) // fmul.s fa0,fa0,fa0
RUAPU_INSTCODE(d, 0x12a57553) // fmul.d fa0,fa0,fa0
RUAPU_INSTCODE(c, 0x0001952a) // add a0,a0,a0 + nop
RUAPU_INSTCODE(zfa, 0xf0108053) // fli.s ft0, min
RUAPU_INSTCODE(zfh, 0x04007053); // fadd.hs ft0, ft0, ft0
RUAPU_INSTCODE(zfhmin, 0xe4000553) // fmv.x.h a0, ft0
RUAPU_INSTCODE(zicsr, 0xc0102573); // csrr a0, time
RUAPU_INSTCODE(zifencei, 0x0000100f); // fence.i
RUAPU_INSTCODE(zmmul, 0x02a50533) // mul a0,a0,a0

#endif

#undef RUAPU_INSTCODE

struct ruapu_isa_entry
{
    const char* isa;
    ruapu_some_inst inst;
};

#define RUAPU_ISAENTRY(isa) { #isa, (ruapu_some_inst)ruapu_some_##isa },

struct ruapu_isa_entry g_ruapu_isa_map[] = {

#if defined(__i386__) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_X64)
RUAPU_ISAENTRY(mmx)
RUAPU_ISAENTRY(sse)
RUAPU_ISAENTRY(sse2)
RUAPU_ISAENTRY(sse3)
RUAPU_ISAENTRY(ssse3)
RUAPU_ISAENTRY(sse41)
RUAPU_ISAENTRY(sse42)
RUAPU_ISAENTRY(sse4a)
RUAPU_ISAENTRY(xop)
RUAPU_ISAENTRY(avx)
RUAPU_ISAENTRY(f16c)
RUAPU_ISAENTRY(fma)
RUAPU_ISAENTRY(fma4)
RUAPU_ISAENTRY(avx2)
RUAPU_ISAENTRY(avx512f)
RUAPU_ISAENTRY(avx512bw)
RUAPU_ISAENTRY(avx512cd)
RUAPU_ISAENTRY(avx512dq)
RUAPU_ISAENTRY(avx512vl)
RUAPU_ISAENTRY(avx512vnni)
RUAPU_ISAENTRY(avx512bf16)
RUAPU_ISAENTRY(avx512ifma)
RUAPU_ISAENTRY(avx512vbmi)
RUAPU_ISAENTRY(avx512vbmi2)
RUAPU_ISAENTRY(avx512fp16)
// TODO:avx512pf
RUAPU_ISAENTRY(avx512er)
RUAPU_ISAENTRY(avx5124fmaps)
RUAPU_ISAENTRY(avx5124vnniw)
RUAPU_ISAENTRY(avxvnni)
RUAPU_ISAENTRY(avxvnniint8)
RUAPU_ISAENTRY(avxvnniint16)
RUAPU_ISAENTRY(avxifma)
RUAPU_ISAENTRY(amxfp16)
RUAPU_ISAENTRY(amxbf16)
RUAPU_ISAENTRY(amxint8)
RUAPU_ISAENTRY(amxtile)

#elif __aarch64__ || defined(_M_ARM64)
RUAPU_ISAENTRY(neon)
RUAPU_ISAENTRY(vfpv4)
RUAPU_ISAENTRY(cpuid)
RUAPU_ISAENTRY(asimdrdm)
RUAPU_ISAENTRY(asimdhp)
RUAPU_ISAENTRY(asimddp)
RUAPU_ISAENTRY(asimdfhm)
RUAPU_ISAENTRY(bf16)
RUAPU_ISAENTRY(i8mm)
RUAPU_ISAENTRY(mte)
RUAPU_ISAENTRY(sve)
RUAPU_ISAENTRY(sve2)
RUAPU_ISAENTRY(svebf16)
RUAPU_ISAENTRY(svei8mm)
RUAPU_ISAENTRY(svef32mm)
RUAPU_ISAENTRY(pmull)
RUAPU_ISAENTRY(crc32)
RUAPU_ISAENTRY(aes)
RUAPU_ISAENTRY(sha1)
RUAPU_ISAENTRY(sha2)
RUAPU_ISAENTRY(sha3)
RUAPU_ISAENTRY(sha512)
RUAPU_ISAENTRY(sm3)
RUAPU_ISAENTRY(sm4)
RUAPU_ISAENTRY(amx)

#elif __arm__ || defined(_M_ARM)
RUAPU_ISAENTRY(half)
RUAPU_ISAENTRY(edsp)
RUAPU_ISAENTRY(neon)
RUAPU_ISAENTRY(vfpv4)
RUAPU_ISAENTRY(idiv)

#elif __mips__
RUAPU_ISAENTRY(msa)

#elif __powerpc__
RUAPU_ISAENTRY(vsx)

#elif __s390x__
RUAPU_ISAENTRY(zvector)

#elif __loongarch__
RUAPU_ISAENTRY(lsx)
RUAPU_ISAENTRY(lasx)

#elif __riscv
RUAPU_ISAENTRY(i)
RUAPU_ISAENTRY(m)
RUAPU_ISAENTRY(a)
RUAPU_ISAENTRY(f)
RUAPU_ISAENTRY(d)
RUAPU_ISAENTRY(c)
RUAPU_ISAENTRY(zfa)
RUAPU_ISAENTRY(zfh)
RUAPU_ISAENTRY(zfhmin)
RUAPU_ISAENTRY(zicsr)
RUAPU_ISAENTRY(zifencei)
RUAPU_ISAENTRY(zmmul)

#elif __openrisc__
RUAPU_ISAENTRY(orbis32)
RUAPU_ISAENTRY(orbis64)
RUAPU_ISAENTRY(orfpx32)
RUAPU_ISAENTRY(orfpx64)
RUAPU_ISAENTRY(orvdx64)

#endif
};

#undef RUAPU_ISAENTRY

const char* g_ruapu_isa_supported[sizeof(g_ruapu_isa_map) / sizeof(g_ruapu_isa_map[0]) + 1] = { 0 };

#if defined __openrisc__
static void ruapu_detect_openrisc_isa()
{
    uint32_t value;
    uint16_t addr = U(0x0000);
    asm volatile ("l.mfspr %0, r0, %1" : "=r" (value) : "K" (addr));
    size_t j = 0;
    for (size_t i = 0; i < sizeof(g_ruapu_isa_map) / sizeof(g_ruapu_isa_map[0]); i++)
    {
        int capable = ((value) >> (5 + i)) & 0x1;
        if (capable)
        {
            g_ruapu_isa_supported[j] = g_ruapu_isa_map[i].isa;
            j++;
        }
    }
    g_ruapu_isa_supported[j] = 0;
}
#endif

void ruapu_init()
{
#if defined _WIN32 || defined __ANDROID__ || defined __linux__ || defined __APPLE__ || defined __FreeBSD__ || defined __NetBSD__ || defined __OpenBSD__ || defined __DragonFly__ || defined __sun__ || defined __SYTERKIT__
    size_t j = 0;
    for (size_t i = 0; i < sizeof(g_ruapu_isa_map) / sizeof(g_ruapu_isa_map[0]); i++)
    {
        int capable = ruapu_detect_isa(g_ruapu_isa_map[i].inst);
        if (capable)
        {
            g_ruapu_isa_supported[j] = g_ruapu_isa_map[i].isa;
            j++;
        }
    }
    g_ruapu_isa_supported[j] = 0;
#elif defined __openrisc__
    ruapu_detect_openrisc_isa();
#else 
    // initialize g_ruapu_isa_map for baremetal here, default all zero
    // there is still ruapu_some_XYZ() functions available
    // but you have to work out your own signal handling
#warning ruapu does not support your baremetal os yet
#endif
}

int ruapu_supports(const char* isa)
{
    const char* const* isa_supported = g_ruapu_isa_supported;
    while (*isa_supported)
    {
        if (strcmp(*isa_supported, isa) == 0)
            return 1;

        isa_supported++;
    }

    return 0;
}

const char* const* ruapu_rua()
{
    return g_ruapu_isa_supported;
}

#endif // RUAPU_IMPLEMENTATION

#ifdef __cplusplus
}
#endif

#endif // RUAPU_H
