// TAGRELEASE: PUBLIC
#include "NativeCamera.h"
#include "NvAppBase/NvFramerateCounter.h"
#include "NV/NvStopWatch.h"
#include "NvAssetLoader/NvAssetLoader.h"
#include "NvUI/NvTweakBar.h"
#include "NV/NvLogs.h"
#include "NvGLUtils/NvGLSLProgram.h"
#include "ImageSave.h"

NativeCamera::NativeCamera(NvPlatformContext* platform) :
		NvSampleApp(platform, "NativeCamera"), m_useRawCapture(false), m_takeShot(
				false) {
	m_framerate.reset(new NvFramerateCounter(this));
	m_viewAspectRatio = 1.0f;
	m_imgAspectRatio = 1.0f;

	// Required in all subclasses to avoid silent link issues
	forceLinkHack();
}

NativeCamera::~NativeCamera() {
	LOGI("NativeCamera: destroyed\n");
}

void NativeCamera::configurationCallback(NvEGLConfiguration& config) {
	config.depthBits = 24;
	config.stencilBits = 0;
	config.apiVer = NvGfxAPIVersionGL4();
}

void NativeCamera::initUI() {
	// sample apps automatically have a tweakbar they can use.
	if (mTweakBar) { // create our tweak ui
		mTweakBar->addValue("RAW capture", m_useRawCapture);
		mTweakBar->addValue("AE - lock", m_AELock);
		mTweakBar->addValue("AE - compensation", m_AECompensation,
				m_staticProperties.control.aeMinExposureCompensation,
				m_staticProperties.control.aeMaxExposureCompensation,
				m_staticProperties.control.aeExposureCompensationStep);

		mTweakBar->addPadding();
		mTweakBar->addValue("Lock exposure", m_request.settings.control.aeLock);
		mTweakBar->addValue("Sensitivity", mSensitivity,
				m_staticProperties.sensor.minSensitivity,
				m_staticProperties.sensor.maxSensitivity);
		mTweakBar->addValue("Exposure (us)", mExposureTime,
				m_staticProperties.sensor.minExposure, 33333);
		mTweakBar->addValue("take picture", m_takeShot, true);
		mTweakBar->syncValues();
	}
}

void NativeCamera::focusChanged(bool focused) {
	LOGI("focusChanged: %d", focused);
	if (focused) {
		startCamera();
	} else {
		stopCamera();
	}
}

void NativeCamera::initRendering(void) {

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	NvAssetLoaderAddSearchPath("gl4-kepler/NativeCamera");

	if (!requireMinAPIVersion(NvGfxAPIVersionGL4()))
		return;

	m_progYUV.reset(
			NvGLSLProgram::createFromFiles("shaders/plain.vert",
					"shaders/yuv.frag"));

	m_progRAW.reset(
			NvGLSLProgram::createFromFiles("shaders/plain.vert",
					"shaders/raw16.frag"));

	setupStreamTextures(m_streamYUV.get(), m_imgTextures);
	setupStreamTextures(m_streamRAW.get(), &m_imgTextures[3]);

}

void NativeCamera::reshape(int32_t width, int32_t height) {
	glViewport(0, 0, (GLint) width, (GLint) height);
	m_viewAspectRatio = (float) height / (float) width;

	CHECK_GL_ERROR();
}

void NativeCamera::startCamera() {
	int status;

	m_cameraManager = nv::camera2::CameraManager::createCameraManager();
	//TODO
	// change all to the front camera.
	status = m_cameraManager->queryStaticProperties(0, m_staticProperties);
	m_cameraDevice = m_cameraManager->createCameraDevice(1, NULL);

	m_streamYUV = setupCameraStream(nv::camera2::YCbCr_420_888);
	m_streamRAW = setupCameraStream(nv::camera2::RAW16);
	m_streamJPG = setupCameraStream(nv::camera2::JPEG);
	capture();
}

void NativeCamera::stopCamera() {
	m_cameraDevice->cancelRequest(m_request.requestId);
	m_streamYUV = nullptr;
	m_streamRAW = nullptr;
	m_streamJPG = nullptr;
	m_cameraDevice = nullptr;
	m_cameraManager = nullptr;
}

std::unique_ptr<nv::camera2::CameraStream> NativeCamera::setupCameraStream(
		nv::camera2::PixelFormat format) {

	if (format == nv::camera2::YCbCr_420_888) {
		m_imgSize = m_staticProperties.scaler.availableYUVSizes[0];
	} else if (format == nv::camera2::RAW16) {
		m_imgSize = m_staticProperties.scaler.availableRAWSizes[2];
	} else {
		m_imgSize = m_staticProperties.scaler.availableJPGSizes[2];
	}

	m_imgAspectRatio = (float) m_imgSize.height / (float) m_imgSize.width;

	return m_cameraDevice->createStream(format, m_imgSize);
}

void NativeCamera::capture() {
	int status;

	m_cameraDevice->initializeDefaultSettings(
			nv::camera2::CAPTURE_INTENT::PREVIEW, m_request);
	m_request.outputs.clear();

	if (m_streamYUV.get() != nullptr) {
		m_request.outputs.push_back(m_streamYUV.get());
	}

	if (m_streamRAW.get() != nullptr) {
		m_request.outputs.push_back(m_streamRAW.get());
	}
	if (m_streamJPG.get() != nullptr) {
		m_request.outputs.push_back(m_streamJPG.get());
	}

	m_request.streaming = true;

	status = m_cameraDevice->capture(m_request);
}

void NativeCamera::setupStreamTextures(const nv::camera2::CameraStream *stream,
		GLuint *textures) {
	uint width, height;
	width = stream->size().width;
	height = stream->size().height;

	glActiveTexture (GL_TEXTURE0);

	if (stream->format() == nv::camera2::RAW16) {
		glGenTextures(1, textures);

		// Setup texture for Y plane
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0,
				GL_LUMINANCE, GL_UNSIGNED_SHORT, (GLvoid*) NULL);

		CHECK_GL_ERROR();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	} else if (stream->format() == nv::camera2::YCbCr_420_888) {
		glGenTextures(3, textures);

		// Setup texture for Y plane
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0,
				GL_LUMINANCE, GL_UNSIGNED_BYTE, (GLvoid*) NULL);

		CHECK_GL_ERROR();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Setup texture for U plane
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width / 2, height / 2, 0,
				GL_LUMINANCE, GL_UNSIGNED_BYTE, (GLvoid*) NULL);
		CHECK_GL_ERROR();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Setup texture for V plane
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width / 2, height / 2, 0,
				GL_LUMINANCE, GL_UNSIGNED_BYTE, NULL);
		CHECK_GL_ERROR();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
}

void NativeCamera::drawStreamImage(const nv::camera2::CameraStream *stream,
		GLuint *textures) {
	float edgeX, edgeY;

	if (m_imgAspectRatio < m_viewAspectRatio) {
		edgeX = 1.0f;
		edgeY = 1.0f;
	}
	// View is taller than image - use entire width, center height
	else {
		edgeX = 1.0f;
		edgeY = 1.0f;
	}

	float const vertexPosition[] = { edgeX, -edgeY, -edgeX, -edgeY, edgeX,
			edgeY, -edgeX, edgeY };

	float const textureCoord[] = { 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			0.0f };

	if (stream->format() == nv::camera2::YCbCr_420_888) {
		glUseProgram(m_progYUV->getProgram());

		for (uint i = 0; i < 3; ++i) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures[i]);
		}

		glUniform1i(m_progYUV->getUniformLocation("uYTex"), 0);
		glUniform1i(m_progYUV->getUniformLocation("uUTex"), 1);
		glUniform1i(m_progYUV->getUniformLocation("uVTex"), 2);

		int aPosCoord = m_progYUV->getAttribLocation("aPosition");
		int aTexCoord = m_progYUV->getAttribLocation("aTexCoord");

		glVertexAttribPointer(aPosCoord, 2, GL_FLOAT, GL_FALSE, 0,
				vertexPosition);
		glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE, 0,
				textureCoord);
		glEnableVertexAttribArray(aPosCoord);
		glEnableVertexAttribArray(aTexCoord);

	} else if (stream->format() == nv::camera2::RAW16) {
		glUseProgram(m_progRAW->getProgram());
		glActiveTexture (GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glUniform1i(m_progRAW->getUniformLocation("uRAWTex"), 0);
		CHECK_GL_ERROR();

		int aPosCoord = m_progRAW->getAttribLocation("aPosition");
		int aTexCoord = m_progRAW->getAttribLocation("aTexCoord");

		glVertexAttribPointer(aPosCoord, 2, GL_FLOAT, GL_FALSE, 0,
				vertexPosition);
		glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE, 0,
				textureCoord);
		glEnableVertexAttribArray(aPosCoord);
		glEnableVertexAttribArray(aTexCoord);
	}

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	for (uint i = 0; i < 3; ++i) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	CHECK_GL_ERROR();
}

/**
 *Check saturation will return 0 or 1 based on the given camera frame.
 *@params: nv::camera2::CameraFrame &f is the cameraframe to be tested on after the camera shot.
 *Returns: 0 if not 20% saturated. 1 if >20% saturated.
 *liuliu
 */
int NativeCamera::checkSaturation(nv::camera2::Statistics stats) {
	unsigned b = stats.histogram.numBuckets;

	unsigned cdf[256];
	cdf[0] = stats.histogram.data.at(0);
	// building the cummulative distribution curve inside cdf, so
	// each bin correspond to the area under the curve of histogram.
	for (unsigned i = 1; i < b; i++) {
		cdf[i] = cdf[i - 1] + stats.histogram.data.at(i);
	}
	unsigned saturatedPixels = cdf[b - 1] - cdf[b - 2];
	LOGI("saturated pixels: %d, total number: %d, with value %d\n",
			saturatedPixels, cdf[b - 1], (10 * saturatedPixels) / cdf[b - 1]);
	//the same thing as without 10 and compare that to 20%
	if ((10 * saturatedPixels) / cdf[b - 1] < 2)
		return 0;
	return 1;
}

void NativeCamera::draw(void) {
	// If the streams have not been created
	if (m_streamYUV == nullptr || m_streamRAW == nullptr
			|| m_streamJPG == nullptr) {
		return;
	}

	std::unique_ptr<nv::camera2::CameraFrame> frameYUV, frameRAW, frameJPG;
	frameYUV = m_streamYUV->dequeue(nv::camera2::WAIT_FOREVER);
	frameRAW = m_streamRAW->dequeue(nv::camera2::WAIT_FOREVER);
	frameJPG = m_streamJPG->dequeue(0);

	glClearColor(0.2f, 0.0f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (m_useRawCapture) {
		uploadImage(*(frameRAW->imageBuffer.get()), &m_imgTextures[3]);
		drawStreamImage(m_streamRAW.get(), &m_imgTextures[3]);

	} else {
		uploadImage(*(frameYUV->imageBuffer.get()), m_imgTextures);
		drawStreamImage(m_streamYUV.get(), m_imgTextures);
	}

	// this is where you can adjust settings to the request.
	// after the program calls capture, the requested image will be returned and displayed on the screen.

	//set the control mode to turn off the 3A algorithm
	m_request.settings.control.mode = nv::camera2::CONTROL_MODE::OFF;
	m_request.settings.sensor.sensitivity = mSensitivity;
	m_request.settings.sensor.exposure = mExposureTime;
	m_request.settings.control.aeLock = m_AELock;
	m_request.settings.control.aeExposureCompensation = m_AECompensation;

	//enable histogram
	m_request.settings.statistics.enableHistogram = true;

	m_cameraDevice->capture(m_request);
	//LOGI("20% saturation yes or no %.2f",checkSaturation(frameJPG->statistics));
	// print fps
	if (m_framerate->nextFrame()) {
		LOGI("fps: %.2f", m_framerate->getMeanFramerate());
	}

	if (m_takeShot) {
		LOGI("take shot command received.");

		stm << test;
		fName = "hw1" + stm.str();
		stm.str("");
		stm.clear();
		ImageSave::writeJPG(*(frameJPG->imageBuffer.get()), fName);
		test++;

		LOGI("take shot command revoked. ");
		m_takeShot = false;

		//}

	}
}

void NativeCamera::uploadImage(nv::camera2::CameraBuffer &img,
		GLuint *textures) {

	nv::camera2::CameraBuffer::Data imgPlane;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	if (img.format() == nv::camera2::YCbCr_420_888) {
		for (uint i = 0; i < 3; i++) {
			imgPlane = img.data(i);
			glPixelStorei(GL_UNPACK_ROW_LENGTH, imgPlane.stride);

			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures[i]);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, imgPlane.width,
					imgPlane.height, GL_LUMINANCE, GL_UNSIGNED_BYTE,
					(GLvoid*) imgPlane.ptr);

			glBindTexture(GL_TEXTURE_2D, 0);
			CHECK_GL_ERROR();
		}
	} else if (img.format() == nv::camera2::RAW16) {
		imgPlane = img.data(0);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, imgPlane.stride);

		glActiveTexture (GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, imgPlane.width, imgPlane.height,
				GL_LUMINANCE, GL_UNSIGNED_SHORT, (GLvoid*) imgPlane.ptr);

		glBindTexture(GL_TEXTURE_2D, 0);
		CHECK_GL_ERROR();
	}
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
}

NvAppBase * NvAppFactory(NvPlatformContext * platform) {
	return new NativeCamera(platform);
}
