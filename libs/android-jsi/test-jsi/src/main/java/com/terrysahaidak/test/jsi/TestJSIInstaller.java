package com.terrysahaidak.test.jsi;

public class TestJSIInstaller {
    public native void installBinding(long javaScriptContextHolder);

    static {
        System.loadLibrary("test-jsi");
    }

    public static String runTest() {
        return "Hello from Java via JNI+JSI";
    }
}
