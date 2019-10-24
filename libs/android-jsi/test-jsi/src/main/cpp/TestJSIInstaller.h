#pragma once

#include <jni.h>
#include "../../../../../../node_modules/react-native/ReactCommon/jsi/jsi/jsi.h"


extern "C" {
    JNIEXPORT void JNICALL
    Java_com_terrysahaidak_test_jsi_TestJSIInstaller_installBinding(JNIEnv* env, jobject thiz, jlong runtimePtr);
}

class SampleModule : public facebook::jsi::HostObject {
public:
    static void install(
            facebook::jsi::Runtime &runtime,
            const std::shared_ptr<SampleModule> sampleModule
    );

    facebook::jsi::Value get(facebook::jsi::Runtime &runtime, const facebook::jsi::PropNameID &name) override;


};