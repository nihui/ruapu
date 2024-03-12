
#ifndef DLL_EXPORT
#ifdef _WIN32
#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif
#else
#define DLL_EXPORT __attribute__((visibility("default")))
#endif
#endif

#define RUAPU_IMPLEMENTATION
#include "ruapu.h"

DLL_EXPORT void ruapu_init_c()
{
    ruapu_init();
}

DLL_EXPORT int ruapu_supports_c(const char* isa)
{
    return ruapu_supports(isa);
}

DLL_EXPORT const char* const* ruapu_rua_c()
{
    return ruapu_rua();
}
