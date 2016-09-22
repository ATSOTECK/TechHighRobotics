#include "CameraObjectFinder.h"
#include "math.h"

float CameraObject::sizeToZ(float realSize) {
    return realSize/size;
}

float CameraObject::yAngleToZ(float heightDif) {
    return heightDif/tan(yAngle);
}

CameraObjectFinder::CameraObjectFinder(AxisCamera* ncamera) {
    camera = ncamera;
    best = NULL;
    height = width = 0; //to be initialized when first image comes in
    
}

double CameraObjectFinder::toAngle(double x)//converts pixels to degrees
{
	x = 2*x/width - 1;
	x = atan(x/1.73205) * 180 / 3.14159;
	return x;
}

void CameraObjectFinder::update() {
    if (camera->IsFreshImage()) {
		ColorImage *image = camera->GetImage();
		width = image->GetWidth();
		height = image->GetHeight();
		delete best;
		best = findObject(image); //find best object canidate
		delete image;
		if(best != NULL)
		{
			double xAngle = toAngle(best->xAngle);//convert everything to degrees
			double yAngle = toAngle(best->yAngle);
			best->xAngle = xAngle;
			best->yAngle = yAngle;
		}
	}
}

bool CameraObjectFinder::isObject() {
    if(best == NULL)
        return false;
    return true;
}

CameraObject* CameraObjectFinder::getObject() {
    return best;
}
    
