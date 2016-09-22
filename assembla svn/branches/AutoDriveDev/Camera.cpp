#include "Camera.h"

AxisCamera* initCamera()
{
    AxisCamera* camera = new AxisCamera();
    camera = &AxisCamera::GetInstance();
	camera->WriteResolution(AxisCameraParams::kResolution_160x120);//Set resolution
    camera->WriteBrightness(0);//Set brightness
	camera->WriteMaxFPS(5);
	return camera;
}
