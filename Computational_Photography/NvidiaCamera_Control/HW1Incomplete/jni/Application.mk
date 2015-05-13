# Need to use GCC 4.8 to fix DIV mismatch issue.
NDK_TOOLCHAIN_VERSION=4.8
 
#APP_ABI
#    By default, the NDK build system will generate machine code for the
#    'armeabi' ABI. This corresponds to an ARMv5TE based CPU with software
#    floating point operations. You can use APP_ABI to select a different
#    ABI.
#
#    For example, to support hardware FPU instructions on ARMv7 based devices,
#    use:
APP_ABI := armeabi-v7a


#APP_STL
#    By default, the NDK build system provides C++ headers for the minimal
#    C++ runtime library (/system/lib/libstdc++.so) provided by the Android
#    system.
#
#    However, the NDK comes with alternative C++ implementations that you can
#    use or link to in your own applications. Define APP_STL to select one of
#    them. Examples are:
#
#       APP_STL := stlport_static    --> static STLport library
#       APP_STL := stlport_shared    --> shared STLport library
#       APP_STL := system            --> default C++ runtime library

APP_STL := gnustl_static

APP_PLATFORM := android-19

APP_CFLAGS = -gdwarf-2 -DANDROID -DUSE_REGAL