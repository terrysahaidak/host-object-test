
#include <jsi/jsi.h>
#include <jni.h>

#include "TestJSIInstaller.h"

using namespace facebook;

extern "C" JNIEXPORT void JNICALL
Java_com_terrysahaidak_test_jsi_TestJSIInstaller_installBinding(JNIEnv *env, jobject thiz, jlong runtimePtr)
{
    jsi::Runtime &runtime = *(jsi::Runtime *)runtimePtr;

    jsi::String proofString = jsi::String::createFromAscii(runtime, "Hello world!");

    runtime.global().setProperty(runtime, "nativeTest", std::move(proofString));
}
