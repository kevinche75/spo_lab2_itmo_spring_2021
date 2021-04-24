//
// Created by kevinche on 23.04.2021.
//
#include "Main.h"
#include "ntfsutils.h"
void *fs;

/*
 * Class:     Main
 * Method:    print_devices
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_Main_print_1devices(JNIEnv * env, jobject obj){
    print_block_devices();
}

/*
 * Class:     Main
 * Method:    initFS
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_Main_initFS(JNIEnv *env, jobject obj, jstring jpath){
    const char *path= (*env)->GetStringUTFChars(env, jpath, 0);
    fs = init_fs((char *)path);
    if (fs != NULL)
        return (jint)0;
    else
        return (jint)-1;
}

/*
 * Class:     Main
 * Method:    closeFS
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_Main_closeFS(JNIEnv *env, jobject obj){
    close_fs(fs);
};

/*
 * Class:     Main
 * Method:    ls
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Main_ls(JNIEnv *env, jobject obj, jstring jpath){
    const char *path = (*env)->GetStringUTFChars(env, jpath, 0);
    char *output = ls(fs, (char*)path);
    return (*env)->NewStringUTF(env, output);
}

/*
 * Class:     Main
 * Method:    cd
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Main_cd(JNIEnv *env, jobject obj, jstring jpath){
    const char *path = (*env)->GetStringUTFChars(env, jpath, 0);
    char *output = cd(fs, (char*)path);
    return (*env)->NewStringUTF(env, output);
}

/*
 * Class:     Main
 * Method:    pwd
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Main_pwd(JNIEnv *env, jobject obj){
    char *output = pwd(fs);
    return (*env)->NewStringUTF(env, output);
}

/*
 * Class:     Main
 * Method:    cp
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Main_cp(JNIEnv *env, jobject obj, jstring jpath, jstring joutput_path){
    const char *path = (*env)->GetStringUTFChars(env, jpath, 0);
    const char *output_path = (*env)->GetStringUTFChars(env, joutput_path, 0);
    char *output = cp(fs, (char*)path, (char*)output_path);
    return (*env)->NewStringUTF(env, output);
}