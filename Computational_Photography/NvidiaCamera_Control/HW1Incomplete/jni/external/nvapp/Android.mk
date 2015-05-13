LOCAL_PATH := $(NVPACK_PATH)/Samples/GameWorks_Samples/extensions
include $(CLEAR_VARS)

LOCAL_MODULE    := nvappbase
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_SRC_FILES := lib/Tegra-Android/libNvAppBaseD.a
LOCAL_EXPORT_STATIC_LIBS := nveglutil nvui nvgamepad
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE    := nvassetloader
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_SRC_FILES := lib/Tegra-Android/libNvAssetLoaderD.a
include $(PREBUILT_STATIC_LIBRARY)


LOCAL_MODULE    := nveglutil
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_SRC_FILES := lib/Tegra-Android/libNvEGLUtilD.a
LOCAL_EXPORT_LDLIBS := -lEGL -landroid -llog
include $(PREBUILT_STATIC_LIBRARY)


LOCAL_MODULE    := nvgamepad
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_SRC_FILES := lib/Tegra-Android/libNvGamepadD.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE    := nvglutils
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_SRC_FILES := lib/Tegra-Android/libNvGLUtilsD.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE    := nvmodel
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_SRC_FILES := lib/Tegra-Android/libNvModelD.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE    := nvui
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_SRC_FILES := lib/Tegra-Android/libNvUID.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE    := external_half
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/externals/include
LOCAL_SRC_FILES := externals/lib/Tegra-Android/libHalfD.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE    := external_r3
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/externals/include
LOCAL_SRC_FILES := externals/lib/Tegra-Android/libR3D.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE    := external_regal
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/externals/include
LOCAL_SRC_FILES := externals/lib/Tegra-Android/libRegalW_static.a
include $(PREBUILT_STATIC_LIBRARY)