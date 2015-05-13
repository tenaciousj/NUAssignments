// TAGRELEASE: PUBLIC
#ifndef NativeCamera_H
#define NativeCamera_H

#include "NvAppBase/NvSampleApp.h"
#include "NvGLUtils/NvImage.h"

#include "native_camera2/native_camera2.h"

#include <memory>
#include <sstream>
#include <string>

class NvStopWatch;
class NvFramerateCounter;

class NativeCamera: public NvSampleApp {
public:
	NativeCamera(NvPlatformContext* platform);
	~NativeCamera();

	void initUI(void);
	void initRendering(void);
	void focusChanged(bool focused) override;
	void draw(void);
	void reshape(int32_t width, int32_t height);

	void configurationCallback(NvEGLConfiguration& config);
	//check saturation function
	int checkSaturation(nv::camera2::Statistics stats);

protected:
	void drawStreamImage(const nv::camera2::CameraStream *stream,
			GLuint *textures);
	void setupStreamTextures(const nv::camera2::CameraStream *stream,
			GLuint *textures);
	void uploadImage(nv::camera2::CameraBuffer &img, GLuint *textures);

	void startCamera();
	void stopCamera();

	std::unique_ptr<nv::camera2::CameraStream> setupCameraStream(
			nv::camera2::PixelFormat format);
	void capture();

	std::unique_ptr<NvFramerateCounter> m_framerate;
	std::unique_ptr<NvGLSLProgram> m_progYUV;
	std::unique_ptr<NvGLSLProgram> m_progRAW;
	GLuint m_imgTextures[4];
	float m_viewAspectRatio;
	float m_imgAspectRatio;

	// Camera objects
	std::unique_ptr<nv::camera2::CameraManager> m_cameraManager;
	std::unique_ptr<nv::camera2::CameraDevice> m_cameraDevice;
	std::unique_ptr<nv::camera2::CameraStream> m_streamYUV;
	std::unique_ptr<nv::camera2::CameraStream> m_streamRAW;
	std::unique_ptr<nv::camera2::CameraStream> m_streamJPG;
	nv::camera2::StaticProperties m_staticProperties;
	nv::camera2::CaptureRequest m_request;
	nv::camera2::Size m_imgSize;

	// TweakBar
	bool m_useRawCapture = false;
	bool m_AELock = false;
	bool m_takeShot = false;
	float m_AECompensation = 0.0f;
	int test = 0;
	std::ostringstream stm;
	std::string fName;
	uint32_t mSensitivity;
	uint32_t mExposureTime;
};

#endif
