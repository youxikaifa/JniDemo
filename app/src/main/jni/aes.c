//
// Created by Administrator on 2017/11/1.
//
#include <jni.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>

#include "cal.h"
#include "aes.h"

JNIEXPORT jstring JNICALL
Java_cn_zkteco_jnidemo_AES128_getStringFromC(JNIEnv *env, jclass type, jstring info_) {
    const char *info = (*env)->GetStringUTFChars(env, info_, NULL);
    jstring string = (*env)->NewStringUTF(env, info);
    // TODO

    (*env)->ReleaseStringUTFChars(env, info_, info);
    return string;
}

JNIEXPORT jbyteArray JNICALL
Java_cn_zkteco_jnidemo_AES128_aes128_1ecb_1encrypt(JNIEnv *env, jclass type, jbyteArray original_,
                                                   jint original_len, jbyteArray key_) {
    unsigned char *original = (unsigned char *) (*env)->GetByteArrayElements(env, original_, NULL);
    unsigned int originalLen = (unsigned int) original_len;
    unsigned char *key = (unsigned char *) (*env)->GetByteArrayElements(env, key_, NULL);

    // TODO

    unsigned char *inputO = (unsigned char *) malloc(originalLen);
    unsigned char *inputK = (unsigned char *) malloc(16); //秘钥长度

    unsigned char *password = (unsigned char *) malloc(originalLen);

    memset(inputO, 0, originalLen);
    memcpy(inputO, original, originalLen);

    memset(inputK, 0, 16);
    memcpy(inputK, key, 16);

    AES128_ECB_encrypt(inputO, originalLen, inputK, password);

    //释放资源
    free(inputK);
    free(inputO);

    (*env)->ReleaseByteArrayElements(env, original_, (jbyte *) original, JNI_ABORT);
    (*env)->ReleaseByteArrayElements(env, key_, (jbyte *) key, JNI_ABORT);

    //设置返回变量
    jbyteArray jb = (*env)->NewByteArray(env, originalLen);
    (*env)->SetByteArrayRegion(env, jb, 0, originalLen, (jbyte *) password);
    return jb;
}


JNIEXPORT jbyteArray JNICALL
Java_cn_zkteco_jnidemo_AES128_aes128_1ecb_1decrypt(JNIEnv *env, jclass type, jbyteArray password_,
                                                   jint password_len, jbyteArray key_) {
    unsigned char *password = (unsigned char *) (*env)->GetByteArrayElements(env, password_, NULL);
    unsigned int passwordLen = (unsigned int) password_len;
    unsigned char *key = (unsigned char *) (*env)->GetByteArrayElements(env, key_, NULL);

    unsigned char *original = (unsigned char *) malloc(passwordLen);
    // TODO

    AES128_ECB_decrypt(password, passwordLen, key, original);

    jbyteArray jba = (*env)->NewByteArray(env, passwordLen);


    (*env)->SetByteArrayRegion(env, jba, 0, passwordLen, (const jbyte *) original);

    free(original); //释放资源

    (*env)->ReleaseByteArrayElements(env, password_, (jbyte *) password, JNI_ABORT);
    (*env)->ReleaseByteArrayElements(env, key_, (jbyte *) key, JNI_ABORT);

    return jba;
}

JNIEXPORT jint JNICALL
Java_cn_zkteco_jnidemo_AES128_callAaddB(JNIEnv *env, jclass type, jint a, jint b) {
    // TODO

    return a + b;
}

JNIEXPORT jboolean JNICALL
Java_cn_zkteco_jnidemo_AES128_getBooleanValue(JNIEnv *env, jclass type, jboolean value) {
    // TODO

    return value;
}

JNIEXPORT jchar JNICALL
Java_cn_zkteco_jnidemo_AES128_getChar(JNIEnv *env, jclass type, jchar c) {

    // TODO
    return c;
}

JNIEXPORT jobject JNICALL
Java_cn_zkteco_jnidemo_AES128_getPersonInfo(JNIEnv *env, jclass type, jobject p) {
//
//    // TODO
    jmethodID methodId;
    //获得customer对象的句柄
    jclass cls_objClass = (*env)->GetObjectClass(env, p); //获取类的一种方式
    //获得customer对象中特定方法getName的id
    methodId = (*env)->GetMethodID(env, cls_objClass, "getName", "()Ljava/lang/String;");
    if (methodId == NULL) {
        return NULL;
    }
    //调用customer对象的特定方法getName
    jstring js_name = (jstring) (*env)->CallObjectMethod(env, p, methodId, NULL);


    jclass clazz = (*env)->FindClass(env, "cn/zkteco/jnidemo/Person");//获取类的另一种方式

    if (clazz == 0)
        return 0;

    jobject jo = (*env)->AllocObject(env, clazz);

    jfieldID fieldId = (*env)->GetFieldID(env, clazz, "name", "Ljava/lang/String;");

    (*env)->SetObjectField(env, jo, fieldId, (*env)->NewStringUTF(env, "Jin"));

    return jo;


}


JNIEXPORT jobject JNICALL
Java_cn_zkteco_jnidemo_AES128_getListPerson(JNIEnv *env, jobject instance) {

    jclass list_cls = (*env)->FindClass(env, "java/util/ArrayList");//获得ArrayList类引用

    if (list_cls == NULL) {
        return NULL;
    }
    jmethodID list_costruct = (*env)->GetMethodID(env, list_cls, "<init>", "()V"); //获得ArrayList的构造函数Id

    jobject list_obj = (*env)->NewObject(env, list_cls, list_costruct); //创建一个Arraylist集合对象

    //或得Arraylist类中的 add()方法ID，其方法原型为： boolean add(Object object) ;
    jmethodID list_add = (*env)->GetMethodID(env, list_cls, "add", "(Ljava/lang/Object;)Z"); //不需要<>

    jclass p_cls = (*env)->FindClass(env, "cn/zkteco/jnidemo/Person");//获得Person类引用

    //获得该类型的构造函数  函数名为 <init> 返回类型必须为 void 即 V
    jmethodID p_costruct = (*env)->GetMethodID(env, p_cls, "<init>", "(Ljava/lang/String;I)V");

    for (int i = 0; i < 3; i++) {
        jstring str = (*env)->NewStringUTF(env, "Jin");
        //通过调用该对象的构造函数来new 一个 Student实例
        jobject stu_obj = (*env)->NewObject(env, p_cls, p_costruct, str, 10);  //构造一个对象

        (*env)->CallBooleanMethod(env, list_obj, list_add, stu_obj); //执行Arraylist类实例的add方法，添加一个stu对象
    }

    return list_obj;
}