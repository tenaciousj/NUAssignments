/* Copyright (c) 2014, NVIDIA CORPORATION. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef NATIVE_CAMERA2_H_
#define NATIVE_CAMERA2_H_


#include <vector>
#include <memory>
#include <cstdint>

namespace nv
{

namespace camera2
{

class CameraDeviceCallbacks;
class CameraDevice;
class CameraStream;
class CameraManager;
class CameraBuffer;
struct StaticProperties;

/*!
 * A structure representing 2D size
 */
struct Size
{
    uint32_t width  = 0;
    uint32_t height = 0;

    Size() = default;
    Size( unsigned w, unsigned h ) :
        width(w), height(h) {}
};

enum PixelFormat
{
    UNKNOWN,
    YCbCr_420_888,
    RAW16,
    JPEG
};

// Matches camera_metadata_enum_android_control_ae_mode
enum class AE_MODE : uint8_t
{
    OFF,
    ON,
    ON_AUTO_FLASH,
    ON_ALWAYS_FLASH,
    ON_AUTO_FLASH_REDEYE
};

// Matches camera_metadata_enum_android_control_ae_state
enum class AE_STATE : uint8_t
{
    INACTIVE,
    SEARCHING,
    CONVERGED,
    LOCKED,
    FLASH_REQUIRED,
    PRECAPTURE
};

// Matches camera_metadata_enum_android_control_ae_precapture_trigger
enum class AE_TRIGGER : uint8_t
{
    IDLE,
    START,
};

// Matches camera_metadata_enum_android_control_af_mode
enum class AF_MODE : uint8_t
{
    OFF,
    AUTO,
    MACRO,
    CONTINUOUS_VIDEO,
    CONTINUOUS_PICTURE,
    MODE_EDOF
};

// Matches camera_metadata_enum_android_control_af_trigger
enum class AF_TRIGGER : uint8_t
{
    IDLE,
    START,
    CANCEL
};


// Matches camera_metadata_enum_control_af_state
enum class AF_STATE : uint8_t
{
    INACTIVE,
    PASSIVE_SCAN,
    PASSIVE_FOCUSED,
    ACTIVE_SCAN,
    FOCUSED_LOCKED,
    NOT_FOCUSED_LOCKED,
    PASSIVE_UNFOCUSED
};


// Matches camera_metadata_enum_android_control_awb_mode
enum AWB_MODE
{
    OFF,
    AUTO,
    INCANDESCENT,
    FLUORESCENT,
    WARM_FLUORESCENT,
    DAYLIGHT,
    CLOUDY_DAYLIGHT,
    TWIGHLIGHT,
    SHADE
};

// Matches camera_metadata_enum_android_control_awb_state
enum class AWB_STATE : uint8_t
{
    INACTIVE,
    SEARCHING,
    CONVERGED,
    LOCKED
};

// Matches camera_metadata_enum_android_flash_mode
enum class FLASH_MODE : uint8_t
{
    OFF,
    SINGLE,
    TORCH
};


// Matches camera_metadata_enum_android_control_capture_intent
enum class CAPTURE_INTENT : uint8_t
{
    CUSTOM,
    PREVIEW,
    STILL_CAPTURE,
    VIDEO_RECORD,
    VIDEO_SNAPSHOT,
    ZERO_SHUTTER_LAG
};

// Matches camera_metadata_enum_android_control_mode
enum class CONTROL_MODE : uint8_t
{
    /*!
     *  Full application control of the pipeline. All
     *  3A routines are disabled, no other control settings
     *  have any effect.
     */
    OFF,

    /*!
     *  Manual control of capture parameters is disabled.
     */
    AUTO,

    /*!
     * Use specific scene mode - not yet supported
     */
    USE_SCENE_MODE
};

struct StaticProperties
{

    int cameraId = -1;

    struct ScalerProperties
    {
        std::vector<PixelFormat> availablePixelFormats;

        std::vector<Size> availableYUVSizes;
        std::vector<Size> availableRAWSizes;
        std::vector<Size> availableJPGSizes;

        std::vector<int32_t> availableYUVMinFrameTimes;
        std::vector<int32_t> availableRAWMinFrameTimes;
        std::vector<int32_t> availableJPGMinFrameTimes;

        float availableMaxDigitalZoom = 0.0f;
    } scaler;

    struct SensorProperties
    {
        int64_t minExposure = -1;
        int64_t maxExposure = -1;
        int32_t minSensitivity = -1;
        int32_t maxSensitivity = -1;
        int64_t maxFrameDuration = -1;
        int32_t activeArraySize[4] = { -1, -1, -1, -1};

        int32_t whiteLevel = -1;
        int32_t blackLevelPattern[4] = { -1, -1, -1, -1};
        float   colorTransformIlluminant1[9];
        float   colorTransformIlluminant2[9];
        int     illuminant1 = -1;
        int     illuminant2 = -1;
    } sensor;

    struct StatisticsProperties
    {
        int32_t histogramBucketCount = -1;
        int32_t maxHistogramCount = -1;
        int32_t maxSharpnessMapValue = -1;
        Size    sharpnessMapSize ;
    } statistics;

    struct LensProperties
    {
        std::vector<float> availableApertures;
        std::vector<float> availableFocalLengths;
        float hyperFocalDistance = -1.0f;
        float minimumFocusDistance = -1.0f;
    } lens;

    struct FlashProperties
    {
        bool available = false;
    } flash;

    struct RequestProperties
    {
        int32_t maxNumRAWStreams = -1 ;
        int32_t maxNumYUVStreams = -1 ;
        int32_t maxNumJPGStreams = -1;
    } request;

    struct ControlProperties
    {
        std::vector<AE_MODE> aeAvailableModes;
        float aeMinExposureCompensation;
        float aeMaxExposureCompensation;
        float aeExposureCompensationStep;

        std::vector<AF_MODE> afAvailableModes;
        std::vector<AWB_MODE> awbAvailableModes;
    } control;
};

struct Request
{
    struct Control
    {
        CONTROL_MODE mode = CONTROL_MODE::OFF;

        bool aeLock = false;
        AE_MODE aeMode = AE_MODE::OFF;
        float aeExposureCompensation = 0.0f;

        AF_MODE afMode = AF_MODE::OFF;

        bool awbLock = false;
        AWB_MODE awbMode = AWB_MODE::OFF;
    };

    struct ControlState
    {
        AE_STATE  aeState;
        AF_STATE  afState;
        AWB_STATE awbState;
    };

    struct Triggers
    {
        AE_TRIGGER aePrecaptureTrigger = AE_TRIGGER::IDLE;
        AF_TRIGGER afTrigger = AF_TRIGGER::IDLE;
    };

    struct Sensor
    {
        int64_t exposure = 20000;       //< exposure time in microseconds;
        int32_t sensitivity = 100;      //< ISO arithmetic units.
        int64_t frameDuration = 33333;      //< frame duration in microseconds.
    };

    struct Lens
    {
        float focusDistance = 0.0f;
    };

    struct Flash
    {
        FLASH_MODE mode = FLASH_MODE::OFF;
    };

    struct Statistics
    {
        bool enableFaceDetection = false;
        bool enableHistogram = false;
        bool enableSharpnessMap = false;
    };
};

struct RequestSettings
{
    CAPTURE_INTENT intent;
    Request::Control    control;
    Request::Triggers   triggers;
    Request::Sensor     sensor;
    Request::Lens       lens;
    Request::Flash      flash;
    Request::Statistics statistics;
};

struct CaptureRequest
{
    int requestId = -1;
    bool streaming = false;      // Indicates a streaming request.
    RequestSettings settings;
    std::vector< CameraStream * > outputs;
};

struct Statistics
{
    struct
    {
        std::vector<unsigned> data;
        unsigned numBuckets;
    } histogram;

    std::vector<float> sharpnessMap;
};

/*
 * Constants to use for timeouts.
 */
constexpr int WAIT_FOREVER = -1;
constexpr int US_PER_MS = 1000;
constexpr int WaitTimeMs( int ms )
{
    return ms * US_PER_MS;
}

/*!
 * Callbacks from the camera device.
 */
class CameraDeviceCallbacks
{
public:

    virtual void onCaptureStarted( int requestId, int64_t timestamp) = 0;
    virtual void onCaptureResults( int requestId ) = 0;

protected:

    CameraDeviceCallbacks() = default;
    CameraDeviceCallbacks( const CameraDeviceCallbacks& ) = delete;
    CameraDeviceCallbacks& operator=( const CameraDeviceCallbacks& ) = delete;
};

/**
 * The CameraManager provides the basic mechanism to query the cameras and
 * connect to a specific device.
 */
class CameraManager
{
public:

    /**
     * Creates an instance of a camera manager.
     */
    static std::unique_ptr<CameraManager> createCameraManager();

    /**
     * Returns the number of cameras in the system
     */
    virtual int getNumberOfCameras() const = 0;

    /*!
     * Fills the StaticProperties structure
     */
    virtual int queryStaticProperties( int cameraId,
            StaticProperties& properties ) = 0;

    /**
     * Connects to a particular camera
     */
    virtual std::unique_ptr<CameraDevice> createCameraDevice(
            unsigned cameraId,
            CameraDeviceCallbacks* callbacks ) = 0;

protected:

    CameraManager() = default;
    CameraManager( const CameraManager& ) = delete;
    CameraManager& operator=( const CameraManager& ) = delete;


};

class CameraFrame
{
public:

    int32_t requestId = 0;   //< The hal's requestId
    bool streaming = false;  //< indicates a repeating request.
    int64_t captureTime = 0; //< begin sensing of first row.

    RequestSettings requestSettings;
    RequestSettings resultSettings;
    Request::ControlState autoControlState;
    Statistics statistics;

    std::unique_ptr<CameraBuffer> imageBuffer;

    CameraFrame() = default;
    virtual ~CameraFrame() = default;
};

class CameraStream
{
public:

    virtual Size size() const = 0;

    virtual PixelFormat format() const = 0;

    /*!
     * Removes a frame from the queue of available frames. This is a blocking
     * call, if no frames are available this call will block until either:
     * 1. A frame becomes available, or
     * 2. The timeoutUs time has passed.
     * Use a timeout of -1 to wait until a frame is received.
     */
    virtual std::unique_ptr<CameraFrame> dequeue( int timeoutUs ) = 0;

    // Returns the number of buffers that are ready to dequeue.
    virtual int numberOfAvailableFrames() = 0;

    virtual ~CameraStream() = default;

protected:

    CameraStream() = default;
    CameraStream( const CameraStream& ) = delete;
    CameraStream& operator=( const CameraStream& ) = delete;
};

class CameraBuffer
{
public:

    enum
    {
        MAX_NUMBER_OF_PLANES = 3
    };

    struct Data
    {
        void* ptr = nullptr;
        int32_t width = 0;
        int32_t height = 0;
        int32_t stride = 0;
        int32_t num_channels = 0;
        int32_t bytes_per_channel = 0;
        int32_t channel_step = 0;
    };

    PixelFormat format() const
    {
        return format_;
    }

    // Get access to the camera buffer data.
    Data data( unsigned plane = 0 )
    {
        return buffer_planes_[plane];
    }

    virtual unsigned numberOfPlanes() const
    {
        return number_of_planes_;
    }

    virtual ~CameraBuffer() = default;

protected:

    /* Will have to derive this class */
    CameraBuffer() = default;

    PixelFormat format_ = UNKNOWN;
    std::array<Data, MAX_NUMBER_OF_PLANES>   buffer_planes_;
    unsigned number_of_planes_ = 0;

};


/**
 * The camera device
 */
class CameraDevice
{
public:

    /*!
     * Creates a new stream. This is a blocking call that will cause a wait
     * until the pipeline is idle.
     * Streams are destroyed when they are deleted.
     */
    virtual std::unique_ptr<CameraStream> createStream( PixelFormat format, Size size ) = 0;

    /**
     * Sets the request with the default values for the specified intent.
     */
    virtual void initializeDefaultSettings( CAPTURE_INTENT intent,
            CaptureRequest& req ) = 0;

    /**
     * capture:
     * Submit a request to the camera pipeline for processing.
     * req.streaming indicates repeating requests.
     * @returns A requestId >= 0 if the request was submitted succesfully.
     *          A value < 0 on error.
     *          For a vector of requests, returns the requestId of the last
     *          request.
     * @note    The request.requestId field is also updated with the requestId.
     */
    virtual int capture(CaptureRequest& req ) = 0;
    virtual int capture(std::vector<CaptureRequest>& reqs) = 0;

    /**
     * Cancel a submitted streaming request.
     */
    virtual int cancelRequest( int requestId ) = 0;


    /*!
     * Virtual destructor.
     * DO NOT REMOVE. Derived classes might implement a destructor.
     */
    virtual ~CameraDevice() {};

protected:

    CameraDevice() = default;
    CameraDevice( const CameraDevice& ) = delete;
    CameraDevice& operator= ( const CameraDevice& ) = delete;
};


}
}


#endif /* NATIVE_CAMERA2_H_ */
