#include "ruapu_binding.h"
#include <stdio.h>

#define RUAPU_IMPLEMENTATION
#include "ruapu.h"

#ifdef __cplusplus
extern "C"
{
#endif

    JNIEXPORT void JNICALL Java_ruapu_Ruapu_init(JNIEnv *env, jclass jcls)
    {
        ruapu_init();
    }

    JNIEXPORT jint JNICALL Java_ruapu_Ruapu_supports(JNIEnv *env, jclass jcls, jstring j_isa)
    {
        const char *isa = (*env)->GetStringUTFChars(env, j_isa, NULL);
        int supported = ruapu_supports(isa);
        (*env)->ReleaseStringUTFChars(env, j_isa, isa);

        return supported;
    }

    JNIEXPORT jobjectArray JNICALL Java_ruapu_Ruapu_rua(JNIEnv *env, jclass jcls)
    {
        const char *const *supported = ruapu_rua();
        size_t size = 0U;
        jclass jStringcls = (*env)->FindClass(env, "java/lang/String");
        while (*supported)
        {
            supported++;
            size++;
        }

        jobjectArray isa_array = (*env)->NewObjectArray(env, (int)size, jStringcls, NULL);

        supported = ruapu_rua();
        while (*supported)
        {
            jstring str_isa = (*env)->NewStringUTF(env, *supported++);
            (*env)->SetObjectArrayElement(env, isa_array, (int)--size, str_isa);
        }
        return isa_array;
    }

#ifdef __cplusplus
}
#endif
