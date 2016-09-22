#include "CameraObjectFinder.h"

float CameraObject::getZ(float realSize) {
    return realSize/size;
}

CameraObjectFinder::CameraObjectFinder(AxisCamera* ncamera) {
    camera = ncamera;
    minScore = 0;
    best = null;
}

double CameraObjectFinder::toAngle(double pixels)
{
	x *= (9.0 / 20.0) / m_xMax;
	x = atan(x);
	x *= 180.0 / 3.14159;
	return x;
}

void CameraObjectFinder::update() {
    if (camera.IsFreshImage()) {
		ColorImage *image = camera.GetImage();
		best = findObject(image);
		delete image;
		double xAngle = toAngle(best->xAngle);
		double yAngle = toAngle(best->yAngle);
		double dist = sqrt(best->xAngle*best->xAngle+best->yAngle*best->yAngle);
		best->size = toAngle(dist+size/2)-toAngle(dist-size/2);
	}
}

bool CameraObjectFinder::isObject() {
    if(best == null)
        return false;
    return true;
}

CameraObject CameraObjectFinder::getObject() {
    return best;
}
    
