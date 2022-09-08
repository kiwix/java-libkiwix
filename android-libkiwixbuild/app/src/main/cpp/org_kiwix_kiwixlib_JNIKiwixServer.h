/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_kiwix_kiwixlib_JNIKiwixServer */

#ifndef _Included_org_kiwix_kiwixlib_JNIKiwixServer
#define _Included_org_kiwix_kiwixlib_JNIKiwixServer
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_kiwix_kiwixlib_JNIKiwixServer
 * Method:    setRoot
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_kiwix_kiwixlib_JNIKiwixServer_setRoot
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_kiwix_kiwixlib_JNIKiwixServer
 * Method:    setAddress
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_kiwix_kiwixlib_JNIKiwixServer_setAddress
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_kiwix_kiwixlib_JNIKiwixServer
 * Method:    setPort
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_kiwix_kiwixlib_JNIKiwixServer_setPort
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_kiwix_kiwixlib_JNIKiwixServer
 * Method:    setNbThreads
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_kiwix_kiwixlib_JNIKiwixServer_setNbThreads
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_kiwix_kiwixlib_JNIKiwixServer
 * Method:    setTaskbar
 * Signature: (ZZ)V
 */
JNIEXPORT void JNICALL Java_org_kiwix_kiwixlib_JNIKiwixServer_setTaskbar
  (JNIEnv *, jobject, jboolean, jboolean);

/*
 * Class:     org_kiwix_kiwixlib_JNIKiwixServer
 * Method:    setBlockExternalLinks
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_kiwix_kiwixlib_JNIKiwixServer_setBlockExternalLinks
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     org_kiwix_kiwixlib_JNIKiwixServer
 * Method:    start
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_kiwix_kiwixlib_JNIKiwixServer_start
  (JNIEnv *, jobject);

/*
 * Class:     org_kiwix_kiwixlib_JNIKiwixServer
 * Method:    stop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_kiwix_kiwixlib_JNIKiwixServer_stop
  (JNIEnv *, jobject);

/*
 * Class:     org_kiwix_kiwixlib_JNIKiwixServer
 * Method:    getNativeServer
 * Signature: (Lorg/kiwix/kiwixlib/Library;)J
 */
JNIEXPORT jlong JNICALL Java_org_kiwix_kiwixlib_JNIKiwixServer_getNativeServer
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif
