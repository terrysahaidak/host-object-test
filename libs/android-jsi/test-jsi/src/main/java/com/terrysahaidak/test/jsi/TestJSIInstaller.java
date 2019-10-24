package com.terrysahaidak.test.jsi;

public class TestJSIInstaller {
    public native void installBinding(long javaScriptContextHolder);

    private String stringField = "Private field value";

    static {
        System.loadLibrary("test-jsi");
    }

    public static String runTest() {
        return "Static field value";
    }
}
