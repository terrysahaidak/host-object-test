
#include <jsi/jsi.h>
#include <jni.h>

#include "TestJSIInstaller.h"

using namespace facebook;

extern "C" JNIEXPORT void JNICALL
Java_com_terrysahaidak_test_jsi_TestJSIInstaller_installBinding(JNIEnv *env, jobject thiz, jlong runtimePtr)
{
  auto &runtime = *(jsi::Runtime *)runtimePtr;
  auto testBinding = std::make_shared<SampleModule>();

  SampleModule::install(runtime, testBinding);
}

void SampleModule::install(
    jsi::Runtime &runtime,
    const std::shared_ptr<SampleModule> sampleModule
    )
{
  auto testModuleName = "nativeSample";
  auto object = jsi::Object::createFromHostObject(runtime, sampleModule);

  runtime.global().setProperty(runtime, testModuleName, std::move(object));
}


jsi::Value SampleModule::get(
    jsi::Runtime &runtime,
    const jsi::PropNameID &name)
{
  auto methodName = name.utf8(runtime);


  if (methodName == "runTest")
  {
    return jsi::Function::createFromHostFunction(
        runtime,
        name,
        0,
        [](
            jsi::Runtime &runtime,
            const jsi::Value &thisValue,
            const jsi::Value *arguments,
            size_t count) -> jsi::Value {

//            const auto env = facebook::jni::attachCurrentThread();

//            jstring str = env->NewStringUTF("test");
//
//            const char *cStr = env->GetStringUTFChars(str, nullptr);

            return 1;

//                return call_in_attached_thread([&runtime](auto env) -> jsi::Value  {
//                    jstring str = env->NewStringUTF("test");
//                    const char *cStr = env->GetStringUTFChars(str, nullptr);
//
//                    auto result = jsi::String::createFromAscii(runtime, cStr);
//
//                    return result;
//                });

//                  auto clazz = jniEnv.FindClass("com/terrysahaidak/test/jsi/TestJSIInstaller");

//                  auto runTest = jniEnv.GetMethodID(clazz, "runTest", "()Ljava/lang/String;");
//                  auto str = (jstring)jniEnv.CallObjectMethod(clazz, runTest);

        });
  }

  return jsi::Value::undefined();
}

//JavaVM *java_machine;
//jint JNI_OnLoad(JavaVM *vm, void *reserved) {
//    java_machine = vm;
//}
