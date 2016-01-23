/*
 * Camaera.h
 *
 *  Created on: Mar 9, 2015
 *      Author: cbf
 */

#pragma once
#include <NIIMAQdx.h>
#include <nivision.h>

class Camera {
private:
	static IMAQdxCameraInformation camInfo[6];
	static Camera *cameras[6];	// array of ourselves
	static uInt32 cameraCount;
	static uInt32 currentCamera;
	static bool debugOutput;
	Image *frame;
	IMAQdxSession session;
	IMAQdxError imaqError;
	uInt32 camera;
	bool firstTime;
	static bool enabled;
	static bool overlay;

public:
	explicit Camera(uInt32 i);
	void DumpAttrs();
	void DumpModes();
	IMAQdxError SetMode();
	bool SetVideoMode(unsigned int x, unsigned int y, unsigned int fps, bool useJpeg);
	static int EnumerateCameras();
	static uInt32 SwitchCamera();
	static void StartCameras();
	static void StopCameras();
	static void Feed(int ticks);
	static char *GetName();
	static char *GetModel();
	static void EnableCameras();
	static void DisableCameras();
	static bool IsEnabled();
	static bool IsOpen();
	static void ToggleOverlay();

	IMAQdxError Start();
	IMAQdxError GetFrame();
	IMAQdxError Stop();

};
