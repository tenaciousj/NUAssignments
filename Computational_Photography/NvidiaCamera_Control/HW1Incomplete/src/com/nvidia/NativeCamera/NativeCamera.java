// TAGRELEASE: PUBLIC
package com.nvidia.NativeCamera;

import android.app.NativeActivity;
import android.os.Bundle;
import android.util.Log;

import com.nvidia.NvAppBase.NvAppBase;

public class NativeCamera extends NvAppBase
{
    @Override
    protected void onCreate (Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        Log.v("NativeCamera", "Calling subclass onCreate");
    }

    static {
        System.loadLibrary("native_camera2");
    }

}
