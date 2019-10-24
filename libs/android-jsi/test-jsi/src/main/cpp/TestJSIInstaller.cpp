
#include "../../../../../../node_modules/react-native/ReactCommon/jsi/jsi/jsi.h"
#include <jni.h>

#include "TestJSIInstaller.h"

using namespace facebook;

JNIEnv *g_env;

extern "C" JNIEXPORT void JNICALL
Java_com_terrysahaidak_test_jsi_TestJSIInstaller_installBinding(JNIEnv *env, jobject thiz, jlong runtimePtr)
{
  g_env = env;
  auto &runtime = *(jsi::Runtime *)runtimePtr;
  auto testBinding = std::make_shared<SampleModule>();

  SampleModule::install(runtime, testBinding);
}

void SampleModule::install(
    jsi::Runtime &runtime,
    const std::shared_ptr<SampleModule> sampleModule)
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
          //        auto clazz = env->FindClass("com/terrysahaidak/test/jsi/TestJSIInstaller");
          //        auto runTest = g_env->GetMethodID(clazz, "runTest", "()Ljava/lang/String;");
          //        auto str = (jstring)env->CallObjectMethod(clazz, runTest);
          //
          //        const char *cStr = env->GetStringUTFChars(str, nullptr);

          return jsi::String::createFromAscii(runtime, "Hello wordl");
        });
  }

  return jsi::Value::undefined();
}
