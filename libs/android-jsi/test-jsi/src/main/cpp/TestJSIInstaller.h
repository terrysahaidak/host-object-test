#pragma once

#include <jni.h>
#include "../../../../../../node_modules/react-native/ReactCommon/jsi/jsi/jsi.h"

using namespace facebook;

extern "C" {
    JNIEXPORT void JNICALL
    Java_com_terrysahaidak_test_jsi_TestJSIInstaller_installBinding(JNIEnv* env, jobject thiz, jlong runtimePtr);
}

class SampleModule : public jsi::HostObject {
public:
    static void install(
            jsi::Runtime &runtime,
            const std::shared_ptr<SampleModule> sampleModule
    );

//    SampleModule(JNIEnv *jniEnv);

    jsi::Value get(jsi::Runtime &runtime, const jsi::PropNameID &name) override;
private:
    JNIEnv jniEnv_;
};