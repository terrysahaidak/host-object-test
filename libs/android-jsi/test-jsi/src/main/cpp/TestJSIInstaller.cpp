#include <jsi/jsi.h>
#include <jni.h>

#include "TestJSIInstaller.h"

JavaVM *jvm;

extern "C" JNIEXPORT void JNICALL
Java_com_terrysahaidak_test_jsi_TestJSIInstaller_installBinding(JNIEnv *env, jobject thiz, jlong runtimePtr)
{
  auto &runtime = *(jsi::Runtime *)runtimePtr;
  auto testBinding = std::make_shared<SampleModule>();

  SampleModule::install(runtime, testBinding);

  env->GetJavaVM(&jvm);
}

JNIEnv *attachCurrentThread()
{
  JavaVMAttachArgs args{JNI_VERSION_1_6, nullptr, nullptr};
  JNIEnv *env = nullptr;
  auto result = jvm->AttachCurrentThread(&env, &args);
  return env;
}

void SampleModule::install(
    jsi::Runtime &runtime,
    const std::shared_ptr<SampleModule> sampleModule)
{
  auto testModuleName = "NativeSampleModule";
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
          auto env = attachCurrentThread();

          auto clazz = env->FindClass("com/terrysahaidak/test/jsi/TestJSIInstaller");

          auto runTest = env->GetStaticMethodID(clazz, "runTest", "()Ljava/lang/String;");
          auto str = (jstring)env->CallStaticObjectMethod(clazz, runTest);

          const char *cStr = env->GetStringUTFChars(str, nullptr);

          return jsi::String::createFromAscii(runtime, cStr);
        });
  }

  return jsi::Value::undefined();
}
