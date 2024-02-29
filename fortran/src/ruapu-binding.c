#define RUAPU_IMPLEMENTATION
#include "ruapu.h"

int get_num_isa_supported() {
    int num = 0;
    const char * const * isa_suppported = g_ruapu_isa_supported;
    while (*isa_suppported) {
        num++;
        isa_suppported++;
    }
    return num;
}
