//
// Created by caixi on 17-9-5.
//
#include <jni.h>

#ifndef NATIVEBITMAPFACTORY_NATIVEBITMAPFACTORY_H
#define NATIVEBITMAPFACTORY_NATIVEBITMAPFACTORY_H
#ifdef __cplusplus
extern "C" {
#endif
jobject createBitmap(JNIEnv *env, jobject obj, jint w, jint h, jint config, jboolean hasAlpha,
                     int isMuttable);

JNIEXPORT jboolean JNICALL
Java_com_cxmax_nativebitmapfactory_NativeBitmapFactory_init(JNIEnv *env);

JNIEXPORT jboolean JNICALL
Java_com_cxmax_nativebitmapfactory_NativeBitmapFactory_release(JNIEnv *env);

JNIEXPORT jobject JNICALL
Java_com_cxmax_nativebitmapfactory_NativeBitmapFactory_createBitmap(JNIEnv *env, jobject obj,
                                                                    jint w, jint h, jint config,
                                                                    jboolean hasAlpha);

JNIEXPORT jobject JNICALL
Java_com_cxmax_nativebitmapfactory_NativeBitmapFactory_createBitmap19(JNIEnv *env, jobject obj,
                                                                      jint w, jint h, jint config,
                                                                      jboolean hasAlpha);
};
#endif //NATIVEBITMAPFACTORY_NATIVEBITMAPFACTORY_H
