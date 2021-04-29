//
// Created by kevinche on 23.04.2021.
//
#include "Main.h"
#include "ntfsutils.h"

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
JNIEXPORT jlong JNICALL Java_Main_initFS(JNIEnv *env, jobject obj, jstring jpath){
    const char *path= (*env)->GetStringUTFChars(env, jpath, 0);
    void *fs = init_fs((char *)path);
    if (fs != NULL)
        return (jlong)fs;
    else
        return (jlong)-1;
}

/*
 * Class:     Main
 * Method:    closeFS
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_Main_closeFS(JNIEnv *env, jobject obj, jlong fs){
    close_fs((void *)fs);
};

int count_infos(struct ntfs_ls_info *start){
    int count = 0;
    struct ntfs_ls_info *tmp = start;
    while (tmp != NULL){
        count++;
        tmp = tmp->next;
    }
    return count;
}

/*
 * Class:     Main
 * Method:    ls
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_Main_ls(JNIEnv *env, jobject obj, jstring jpath, jlong fs){
    const char *path = (*env)->GetStringUTFChars(env, jpath, 0);
    struct ntfs_ls_info *start = ls((void *)fs, (char*)path);
    int count = count_infos(start);
    jobjectArray infos = 0;
    count--;
    count*=2;
    infos = (*env)->NewObjectArray(env,count,(*env)->FindClass(env,"java/lang/String"), (*env)->NewStringUTF(env, ""));
    struct ntfs_ls_info *cur = start;
    int i = 0;
    while (cur != NULL){
        jstring dir;
        jstring name;
        if (cur->filename != NULL){
            if (cur->dir == 1){
                dir = (*env)->NewStringUTF(env, "DIR");
            } else {
                dir = (*env)->NewStringUTF(env, "FILE");
            }
            (*env)->SetObjectArrayElement(env, infos, i, dir);
            i++;
            name = (*env)->NewStringUTF(env, cur->filename);
            (*env)->SetObjectArrayElement(env, infos, i, name);
            i++;
        }
        cur = cur->next;
    }
    free_infos(start);
    return infos;
}

/*
 * Class:     Main
 * Method:    cd
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Main_cd(JNIEnv *env, jobject obj, jstring jpath, jlong fs){
    const char *path = (*env)->GetStringUTFChars(env, jpath, 0);
    char *output = cd((void *)fs, (char*)path);
    return (*env)->NewStringUTF(env, output);
}

/*
 * Class:     Main
 * Method:    pwd
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Main_pwd(JNIEnv *env, jobject obj, jlong fs){
    char *output = pwd((void *)fs);
    return (*env)->NewStringUTF(env, output);
}

/*
 * Class:     Main
 * Method:    cp
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Main_cp(JNIEnv *env, jobject obj, jstring jpath, jstring joutput_path, jlong fs){
    const char *path = (*env)->GetStringUTFChars(env, jpath, 0);
    const char *output_path = (*env)->GetStringUTFChars(env, joutput_path, 0);
    char *output = cp((void *)fs, (char*)path, (char*)output_path);
    return (*env)->NewStringUTF(env, output);
}