//
// Created by Administrator on 2017/11/1.
//

#include <jni.h>

#ifndef JNIDEMO_MAIN_H
#define JNIDEMO_MAIN_H


#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jbyteArray JNICALL
Java_cn_zkteco_jnidemo_AES128_aes128_1ecb_1encrypt(JNIEnv *env, jclass type, jbyteArray original_,
                                                   jint original_len, jbyteArray key_);

JNIEXPORT jbyteArray JNICALL
Java_cn_zkteco_jnidemo_AES128_aes128_1ecb_1decrypt(JNIEnv *env, jclass type, jbyteArray password_,
                                                   jint password_len, jbyteArray key_);


JNIEXPORT jint JNICALL
Java_cn_zkteco_jnidemo_AES128_callAaddB(JNIEnv *env, jclass type, jint a, jint b);


JNIEXPORT jboolean JNICALL
Java_cn_zkteco_jnidemo_AES128_getBooleanValue(JNIEnv *env, jclass type, jboolean value);


JNIEXPORT jchar JNICALL
Java_cn_zkteco_jnidemo_AES128_getChar(JNIEnv *env, jclass type, jchar c);


JNIEXPORT jobject JNICALL
Java_cn_zkteco_jnidemo_AES128_getPersonInfo(JNIEnv *env, jclass type, jobject p);


JNIEXPORT jstring JNICALL
Java_cn_zkteco_jnidemo_AES128_getStringFromC(JNIEnv *env, jclass type, jstring info_);


JNIEXPORT jobject JNICALL
Java_cn_zkteco_jnidemo_AES128_getListPerson(JNIEnv *env, jobject instance);

#ifdef __cplusplus
}

#endif
#endif //JNIDEMO_MAIN_H
