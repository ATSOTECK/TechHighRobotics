#ifndef __CAMERA_OBJECT__
#define __CAMERA_OBJECT__

#include <wpilib.h>

class CameraObject {
public:
    float xAngle,yAngle,size,score;
    float getZ(float realSize);
};

class CameraObjectFinder {
protected:
    AxisCamera* camera;
    CameraObject *best;
    double toAngle(double x);//pixels is the distance from perpendicular
    int width,height;
public:
    CameraObjectFinder(AxisCamera* ncamera);
    void update(); //updates the best object if there is a new camera image using findObjects(). converts to angle units.
    bool isObject(); //says if there is an object in the image good enough
    CameraObject* getObject(); //returns best object
    virtual CameraObject *findObject(ColorImage* image) = 0;
};

#endif
