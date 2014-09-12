package com.ivizon.androidcomputesample;

public class NativeComputeLoad {

    static
    {
        System.loadLibrary("android_compute_sample_1");
    }
	public static native void initBoostCompute();
	public static native String getDeviceName();
	public static native int getComputeUnits();
	public static native long getGlobalMemory();
	public static native long getLocalMemory();
	
}

//Right click on project -> Android Tools -> Add native support -> android_compute_sample_1 (library name)
// Restart you eclipse in case it give parser error!

//Manual header creation:
//=======================
// Run the command from project folder root:
// javah -jni -verbose -classpath bin/classes/ -d jni/ com.ivizon.androidcomputesample.NativeComputeLoad

//Eclipse setup:
//==============
//	Run -> External Tools -> External Tool Configuration
//	New program: 
//	Location : usr/bin/javah
//	Working directory: ${workspace_loc:/AndroidComputeSample/bin}
//	Arguments :-verbose -classpath ${project_loc}/bin/classes/ -jni -d ${project_loc}/jni/  ${java_type_name}

//Reference : http://omtlab.com/java-run-javah-from-eclipse/