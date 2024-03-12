#include <jni.h>

#ifndef _Included_Ruapu
#define _Included_Ruapu
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_ruapu_Ruapu_init(JNIEnv *env, jclass jcls);
JNIEXPORT jint JNICALL Java_ruapu_Ruapu_supports(JNIEnv *env, jclass jcls, jstring j_isa);
JNIEXPORT jobjectArray JNICALL Java_ruapu_Ruapu_rua(JNIEnv *env, jclass jcls);

#ifdef __cplusplus
}
#endif
#endif // _Included_Ruapu
