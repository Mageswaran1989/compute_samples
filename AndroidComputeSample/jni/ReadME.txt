

* Right click on project -> Android Tools -> Add native support -> android_compute_sample_1 (library name)
Add C++ standard library header path:
=====================================
Project -> Properties -> C/C++ General -> Paths and sysmbol -> includes and add
below path 
path/to/android-ndk-r10/sources/cxx-stl/stlport/stlport

!!! Restart you eclipse in case it give parser error.

Manual header creation:
=======================
 Run the command from project folder root:
 javah -jni -verbose -classpath bin/classes/ -d jni/ com.ivizon.androidcomputesample.NativeComputeLoad

Eclipse setup:
==============
	Run -> External Tools -> External Tool Configuration
	New program: 
	Location : usr/bin/javah
	Working directory: ${workspace_loc:/AndroidComputeSample/bin}
	Arguments :-verbose -classpath ${project_loc}/bin/classes/ -jni -d ${project_loc}/jni/  ${java_type_name}

Reference : http://omtlab.com/java-run-javah-from-eclipse/


OpenCL library in you Android device is loaded automatically by searching some predefined library paths and libs.
For this I have adopted the work by https://github.com/krrishnarraj/libopencl-stub.

Here I will show how it is integrated as one application with Android.

Download the files from https://github.com/krrishnarraj/libopencl-stub.
* Copy the files pathTo/libopencl-stub/include to pathTo/AndroidComputeSample/jni/ folder.
* Copy libopencl.c also to pathTo/AndroidComputeSample/jni/ folder.


For Boost libraries on Android
* Download the git from https://github.com/MysticTreeGames/Boost-for-Android
* Run .build_android.sh /path/to/android/ndk
* Copy pathTo/Boost-for-Android-master/build/include/boost-1_53/ to pathTo/AndroidComputeSample/jni/
* Copy pathTo/Boost-for-Android-master/build/lib as pathTo/AndroidComputeSample/jni/boost_libs

XXXXXX We are not using all boost headers and libs XXXXXXXX


Please have a look on Android.mk and Application.mk

To Run 
=======

Use the prebuild APK or open the project in your eclipse and teset it on your device.

To see the logs in adb shell: logcat -s AndroidComputeSample_1