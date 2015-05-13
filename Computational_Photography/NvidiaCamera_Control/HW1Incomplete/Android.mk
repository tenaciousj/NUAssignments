# Copyright (c) 2014, NVIDIA CORPORATION. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#  * Neither the name of NVIDIA CORPORATION nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
# OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := native_camera2

LOCAL_CFLAGS += -DHAVE_PTHREADS
LOCAL_CPPFLAGS += -std=c++11
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include

ifeq (1, $(BUILD_NATIVE_CAMERA2))
# Driver source files
LOCAL_SRC_FILES := \
    src/CameraManagerImpl.cpp \
    src/CameraDeviceImpl.cpp \
    src/CameraStreamImpl.cpp \
    src/CameraBufferImpl.cpp \
    src/MetadataHelper.cpp \
    src/MetadataTranslator.cpp

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/include \
	$(LOCAL_PATH)/../../../../include \
	$(ANDROID_TOP)/bionic \
	$(ANDROID_TOP)/system/core/include \
	$(ANDROID_TOP)/hardware/libhardware/include \
	$(ANDROID_TOP)/system/media/camera/include \
	$(ANDROID_TOP)/frameworks/av/services/camera/libcameraservice \
	$(ANDROID_TOP)/frameworks/av/include \
	$(ANDROID_TOP)/frameworks/native/include
	

LOCAL_LDLIBS := -landroid -llog -L$(ANDROID_TOP)/lib -lgui -lutils -lcamera_metadata -lcamera_client -lbinder
include $(BUILD_SHARED_LIBRARY)

else
# Use prebuilt
LOCAL_SRC_FILES := prebuilt/armeabi-v7a/libnative_camera2.so
include $(PREBUILT_SHARED_LIBRARY)

endif

