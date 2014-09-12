LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := android_compute_sample_1
LOCAL_SRC_FILES := libopencl.c android_compute_sample_1.cpp 

LOCAL_CFLAGS   += -fPIC -O2
LOCAL_CPPFLAGS += -fexceptions
LOCAL_LDFLAGS += -llog

include $(BUILD_SHARED_LIBRARY)