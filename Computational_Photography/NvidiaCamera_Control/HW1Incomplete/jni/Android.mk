LOCAL_PATH := $(call my-dir)
NVPACK_PATH := /Users/jeanettepranin1/NvidiaGameworks
include $(CLEAR_VARS)

LOCAL_MODULE    := NativeCamera
LOCAL_CFLAGS += -std=c++11 
LOCAL_SRC_FILES := NativeCamera.cpp ImageSave.cpp
LOCAL_STATIC_LIBRARIES += nvappbase nvui nvassetloader nvglutils nveglutil nvgamepad external_regal
LOCAL_LDLIBS :=  -lEGL -landroid
LOCAL_SHARED_LIBRARIES += native_camera2

include $(BUILD_SHARED_LIBRARY)
$(call import-add-path, /Users/jeanettepranin1/Desktop/EECS_395)
$(call import-add-path, $(LOCAL_PATH)/external)
$(call import-add-path, $(LOCAL_PATH)/../../)

$(call import-module,nvapp)

$(call import-module,native_camera2)

