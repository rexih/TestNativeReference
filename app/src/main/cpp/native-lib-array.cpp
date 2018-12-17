#include <jni.h>
#include <string>
#include <android/log.h>

#define LOG_TAG "JNI_ARRAY"

extern void printRefTable(JNIEnv *env);

void JNICALL swap(char *text, int i, int j) {
    if (i != j) {
        text[i] = text[i] ^ text[j];
        text[j] = text[i] ^ text[j];
        text[i] = text[i] ^ text[j];
    }
}

void JNICALL reverseChars(char *text) {
    size_t len = strlen(text);
    int count = len / 2;
    if (count >= 1) {
        for (int i = 0; i < count; ++i) {
            swap(text, i, len - 1 - i);
        }
    }
}


extern "C"
JNIEXPORT jstring JNICALL
Java_cn_rexih_android_testnativereference_JniManager_echo(JNIEnv *env, jobject instance, jstring text) {
    // java string -> const char*
    const char *byChars = env->GetStringUTFChars(text, NULL);

    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "by GetStringUTFChars:%s", byChars);
    jstring pTemp = env->NewStringUTF(byChars);
    env->DeleteLocalRef(pTemp);

    env->ReleaseStringUTFChars(text, byChars);

    jsize len = env->GetStringUTFLength(text);
    char *regionBuf = new char[len];
    env->GetStringUTFRegion(text, 0, len, regionBuf);

    // const char* -> java string
    reverseChars(regionBuf);
    jstring pRet = env->NewStringUTF(regionBuf);
    delete[] regionBuf;
    return pRet;
}

//void test(JNIEnv *env, jintArray arr) {
//    env->GetIntArrayRegion()
//}

extern "C"
JNIEXPORT jstring JNICALL
Java_cn_rexih_android_testnativereference_JniManager_testChinese(JNIEnv *env, jobject instance) {

    return env->NewStringUTF("it's Chinese: 老司机");
}

extern "C"
JNIEXPORT void JNICALL
Java_cn_rexih_android_testnativereference_JniManager_testObjectArray(JNIEnv *env, jobject instance, jobjectArray objArray) {

    jstring pCurJstring;
    const char *pTmpChar;
    jsize alen = env->GetArrayLength(objArray);
    char **pCharArray = static_cast<char **>(malloc(sizeof(char *) * alen));
    for (int i = 0; i < alen; ++i) {
        pCurJstring = static_cast<jstring>(env->GetObjectArrayElement(objArray, i));
        pTmpChar = env->GetStringUTFChars(pCurJstring, NULL);

        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "before %d: %s", i, pTmpChar);

        size_t clen = strlen(pTmpChar);
        char *pCpChar = static_cast<char *>(malloc(sizeof(char) * clen));
        strcpy(pCpChar, pTmpChar);
        reverseChars(pCpChar);

        pCharArray[alen - 1 - i] = pCpChar;

        env->ReleaseStringUTFChars(pCurJstring, pTmpChar);
        env->DeleteLocalRef(pCurJstring);
    }

    for (int i = 0; i < alen; ++i) {
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "after %d: %s", i, pCharArray[i]);
        free(pCharArray[i]);
    }
    free(pCharArray);
    printRefTable(env);
    return;
}


extern "C"
JNIEXPORT jint JNICALL
Java_cn_rexih_android_testnativereference_JniManager_testRegionArray(JNIEnv *env, jobject instance, jcharArray carr) {

    jsize alen = env->GetArrayLength(carr);
    jchar *pChar = new jchar[alen];
    env->GetCharArrayRegion(carr, 0, alen, pChar);

    int sum = 0;

    for (int i = 0; i < alen; ++i) {
        sum += (int) (pChar[i] - '0');
    }
    printRefTable(env);
    return sum;

}


extern "C" JNIEXPORT jint JNICALL
Java_cn_rexih_android_testnativereference_JniManager_testArrayReleaseMode(
        JNIEnv *env, jobject instance, jintArray test, jint option) {

    jboolean isCopy;
    jint *pInt = env->GetIntArrayElements(test, &isCopy);
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "GetIntArrayElements isCopy: %s", isCopy ? "true" : "false");
    printRefTable(env);
    int a;
    switch (option) {
        case 0:
            // 0
            pInt[2] = pInt[2] + 12;
            env->ReleaseIntArrayElements(test, pInt, 0);
            printRefTable(env);
            a = pInt[1];
            break;
        case JNI_COMMIT:
            // commit
            pInt[2] = pInt[2] + 12;
            env->ReleaseIntArrayElements(test, pInt, JNI_COMMIT);
            printRefTable(env);
            a = pInt[1];
//            env->ReleaseIntArrayElements(test, pInt, JNI_ABORT);
//            printRefTable(env);
            break;
        case JNI_ABORT:
            // abort
            pInt[2] = pInt[2] + 12;
            env->ReleaseIntArrayElements(test, pInt, JNI_ABORT);
            printRefTable(env);
            a = pInt[1];

            break;
    }
    return a;
}

