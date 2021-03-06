#include "CameraObjectFinder.h"
#include "math.h"

float CameraObject::getZ(float realSize) {
    return realSize/size;
}

CameraObjectFinder::CameraObjectFinder(AxisCamera* ncamera) {
    camera = ncamera;
    best = NULL;
    height = width = 0;//to be initialized when first image comes in
}

double CameraObjectFinder::toAngle(double x)//converts pixels to degrees
{
	//x *= (9.0 / 20.0) / width;
	//x = atan(x);
	//x *= 180.0 / 3.14159;
	return x;
}

void CameraObjectFinder::update() {
    if (camera->IsFreshImage()) {
		ColorImage *image = camera->GetImage();
		width = image->GetWidth();
		height = image->GetHeight();
		best = findObject(image);//find best object canidate
		delete image;
		double xAngle = toAngle(best->xAngle);//convert everything to degrees
		double yAngle = toAngle(best->yAngle);
		double dist = sqrt(best->xAngle*best->xAngle+best->yAngle*best->yAngle);
		best->size = toAngle(dist+best->size/2)-toAngle(dist-best->size/2);
		best->xAngle = xAngle;
		best->yAngle = yAngle;
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
    
