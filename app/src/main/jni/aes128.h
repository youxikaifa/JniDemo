//
// Created by Administrator on 2017/10/31.
//
#include <jni.h>

#ifndef JNIDEMO2_AES128_H
#define JNIDEMO2_AES128_H


#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL
Java_cn_zkteco_jnidemo_AES128_getStringFromC(JNIEnv *env, jclass type);

JNIEXPORT jbyteArray JNICALL
Java_cn_zkteco_jnidemo_AES128_aes128_1ecb_1encrypt(JNIEnv *env, jclass type, jbyteArray original_,
                                                   jint original_len, jbyteArray key_);

JNIEXPORT jbyteArray JNICALL
Java_cn_zkteco_jnidemo_AES128_aes128_1ecb_1decrypt(JNIEnv *env, jclass type, jbyteArray password_,
                                                   jint password_len, jbyteArray key_);

unsigned char *
AES128_ECB_encrypt(unsigned char *original, unsigned int original_len, unsigned char *key);

unsigned char *
AES128_ECB_decrypt(unsigned char *password, unsigned int password_len, unsigned char *key);

void ECB_decrypt(const unsigned char *input, const unsigned char *key, unsigned char *output);

void InvCipher(void);

void InvSubBytes(void);

unsigned char getSBoxInvert(unsigned char num);

void InvMixColumns(void);

void InvShiftRows(void);

void KeyExpansion(void);

void AddRoundKey(unsigned char round);

unsigned char xTime(unsigned char x);

void BlockCopy(unsigned char *output, const unsigned char *input);

void ECB_encrypt(const unsigned char *input, const unsigned char *pakey, unsigned char *output);


#ifdef __cplusplus
}
#endif
#endif
