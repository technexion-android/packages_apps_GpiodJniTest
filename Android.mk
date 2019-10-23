LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_STATIC_JAVA_LIBRARIES := android-support-v4
LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := \
        $(call all-java-files-under, src)

LOCAL_PACKAGE_NAME := GPIOD_JNI_TEST
LOCAL_CERTIFICATE := platform

LOCAL_PRIVILEGED_MODULE := false

LOCAL_JNI_SHARED_LIBRARIES := serialport
LOCAL_MODULE_INCLUDE_LIBRARY  := true

LOCAL_REQUIRED_MODULES := gpiod_jni

LOCAL_AAPT_FLAGS += -c zz_ZZ

LOCAL_SDK_VERSION := current

include $(BUILD_PACKAGE)

include $(call all-makefiles-under, jni)
include $(call all-makefiles-under,$(LOCAL_PATH))
