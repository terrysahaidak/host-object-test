#include <jsi/jsi.h>
#include <jni.h>

#include "TestJSIInstaller.h"

// global ref to Java Virtual Machine
// used to get JNI current env
JavaVM *jvm;
// global ref to our class instance
static jobject globalObjectRef;
// global ref to our class
static jclass globalClassRef;

extern "C" JNIEXPORT void JNICALL
Java_com_terrysahaidak_test_jsi_TestJSIInstaller_installBinding(JNIEnv *env, jobject thiz, jlong runtimePtr)
{
  auto &runtime = *(jsi::Runtime *)runtimePtr;
  auto testBinding = std::make_shared<SampleModule>();

  SampleModule::install(runtime, testBinding);

  // storring java vm reference
  env->GetJavaVM(&jvm);

  globalObjectRef = env->NewGlobalRef(thiz);

  auto clazz = env->FindClass("com/terrysahaidak/test/jsi/TestJSIInstaller");

  globalClassRef = (jclass)env->NewGlobalRef(clazz);
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

  if (methodName == "getStaticField")
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

          auto runTest = env->GetStaticMethodID(globalClassRef, "runTest", "()Ljava/lang/String;");
          auto str = (jstring)env->CallStaticObjectMethod(globalClassRef, runTest);

          const char *cStr = env->GetStringUTFChars(str, nullptr);

          return jsi::String::createFromAscii(runtime, cStr);
        });
  }

  if (methodName == "getStringPrivateField")
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

          auto valId = env->GetFieldID(globalClassRef, "stringField", "Ljava/lang/String;");

          auto str = (jstring)env->GetObjectField(globalObjectRef, valId);

          const char *cStr = env->GetStringUTFChars(str, nullptr);

          return jsi::String::createFromAscii(runtime, cStr);
        });
  }

  return jsi::Value::undefined();
}
