#include <jni.h>
#include <string>
#include <android/log.h>

#define LOG_TAG "JNI_REF"

static jclass g_vm_class;
static jmethodID g_dump_mid;

extern void printRefTable(JNIEnv *env) {
    env->CallStaticVoidMethod(g_vm_class, g_dump_mid);
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    if (JNI_OK != vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6)) {
        return -1;
    }
    g_vm_class = static_cast<jclass>(env->NewGlobalRef(env->FindClass("dalvik/system/VMDebug")));
    g_dump_mid = env->GetStaticMethodID(g_vm_class, "dumpReferenceTables", "()V");
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    if (JNI_OK != vm->GetEnv(reinterpret_cast<void **>(env), JNI_VERSION_1_6)) {
        return;
    }
    env->DeleteGlobalRef(g_vm_class);
    g_dump_mid = NULL;
}

extern "C" JNIEXPORT void JNICALL
Java_cn_rexih_android_testnativereference_JniManager_testInitLocalRef(JNIEnv *env,
                                                                      jobject instance, jobject entity) {


    // 标记
    jstring pMark = env->NewStringUTF("I'm a mark");

    // 强制进行 reference table dump
    // 查找了一次VMDebug类，会添加到local ref table中
    jclass vm_class = env->FindClass("dalvik/system/VMDebug");
    jmethodID dump_mid = env->GetStaticMethodID(vm_class, "dumpReferenceTables", "()V");
    env->CallStaticVoidMethod(vm_class, dump_mid);

}

extern "C"
JNIEXPORT void JNICALL
Java_cn_rexih_android_testnativereference_JniManager_testLocalRefOverflow(JNIEnv *env, jobject instance) {


    char a[5];
    // 进入native环境时local ref table就会存在几条引用，所以还没到512时就会溢出
    for (int i = 0; i < 512; ++i) {
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "before:%d", i);
        sprintf(a, "%d", i);
        jstring pJstring = env->NewStringUTF(a);
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "after:%d", i);
    }
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "test finish");
}

extern "C"
JNIEXPORT void JNICALL
Java_cn_rexih_android_testnativereference_JniManager_testDeleteLocalRef(JNIEnv *env, jobject instance) {

    char a[5];
    for (int i = 0; i < 512; ++i) {
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "before:%d", i);
        sprintf(a, "%d", i);
        jstring pJstring = env->NewStringUTF(a);
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "after:%d", i);
        env->DeleteLocalRef(pJstring);
    }
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "test finish");


}

extern "C"
JNIEXPORT void JNICALL
Java_cn_rexih_android_testnativereference_JniManager_testEnsureLocalCapacity(JNIEnv *env, jobject instance) {

    char a[5];
    int capacity = 516;
    for (; capacity > 0; --capacity) {
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "current try alloc :%d", capacity);
        if (0 > env->EnsureLocalCapacity(capacity)) {
            // 内存分配失败, 调用ExceptionOccurred也会返回一个jobject占用local ref table,须释放
            jthrowable pJthrowable = env->ExceptionOccurred();
            env->ExceptionDescribe();
            env->ExceptionClear();
            env->DeleteLocalRef(pJthrowable);
        } else {
            __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "success alloc :%d", capacity);
            break;
        }
    }
    env->CallStaticVoidMethod(g_vm_class, g_dump_mid);
    for (int i = 0; i < capacity; ++i) {
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "before:%d", i + 1);
        sprintf(a, "%d", i + 1);
        jstring pJstring = env->NewStringUTF(a);
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "after:%d", i + 1);
    }
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "test finish");
    env->CallStaticVoidMethod(g_vm_class, g_dump_mid);
}

extern "C"
JNIEXPORT void JNICALL
Java_cn_rexih_android_testnativereference_JniManager_testPushLocalFrame(JNIEnv *env, jobject instance) {

    char a[5];
    int capacity = 516;
    for (; capacity > 0; --capacity) {
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "current try alloc :%d", capacity);
        if (0 > env->PushLocalFrame(capacity)) {
//            if (env->ExceptionCheck()) {
//                env->ExceptionDescribe();
            env->ExceptionClear();
//            }
        } else {
            __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "success alloc :%d", capacity);
            break;
        }
    }
    env->CallStaticVoidMethod(g_vm_class, g_dump_mid);
    jobject lastVal;
    for (int i = 0; i < capacity; ++i) {
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "before:%d", i + 1);
        sprintf(a, "%d", i + 1);
        lastVal = env->NewStringUTF(a);
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "after:%d:addr:%p", i + 1, lastVal);
    }
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "test finish");
    jobject convertThenRetain = env->PopLocalFrame(lastVal);
    env->CallStaticVoidMethod(g_vm_class, g_dump_mid);
}


static jobject g_weak;

extern "C"
JNIEXPORT jobject JNICALL
Java_cn_rexih_android_testnativereference_JniManager_initWeakGlobalRef(JNIEnv *env, jobject instance, jobject entity) {
    g_weak = env->NewWeakGlobalRef(entity);
    return g_weak;
}


extern "C"
JNIEXPORT jobject JNICALL
Java_cn_rexih_android_testnativereference_JniManager_testGetWeakGlobalRef(JNIEnv *env, jobject instance, jobject repl) {
    // 通过IsSameObject判断弱引用是否有效
    if (env->IsSameObject(g_weak, NULL)) {
        return repl;
    } else {
        return g_weak;
    }
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_cn_rexih_android_testnativereference_JniManager_testIsSameObject(JNIEnv *env, jobject instance) {

    return env->IsSameObject(g_vm_class, env->FindClass("dalvik/system/VMDebug"));


}


void printReferenceType(JNIEnv *env, jobject obj, const char *name) {
    jobjectRefType type = env->GetObjectRefType(obj);
    const char *typeDesc;
    switch (type) {
        case JNIInvalidRefType:
            typeDesc = "JNIInvalidRefType";
            break;
        case JNILocalRefType:
            typeDesc = "JNILocalRefType";
            break;
        case JNIGlobalRefType:
            typeDesc = "JNIGlobalRefType";
            break;
        case JNIWeakGlobalRefType:
            typeDesc = "JNIWeakGlobalRefType";
            break;
    }
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "%s is %s", name, typeDesc);

}

extern "C"
JNIEXPORT void JNICALL
Java_cn_rexih_android_testnativereference_JniManager_testReferenceType(JNIEnv *env, jobject instance, jobject entity) {


    if (env->IsSameObject(g_weak, NULL)) {
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "先初始化weak ref");
        return;
    }

    printReferenceType(env, g_weak, "g_weak");
    printReferenceType(env, g_vm_class, "g_vm_class");
    printReferenceType(env, entity, "entity");
    printReferenceType(env, NULL, "null");

}



