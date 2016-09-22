#ifndef __CAMERA_OBJECT__
#define __CAMERA_OBJECT__

#include <wpilib.h>

class CameraObject {
    float xAngle,yAngle,size,score;
    float getZ(float realSize);
};

class CameraObjectFinder {
private:
    AxisCamera* ncamera;
    CameraObject *best;
    double toAngle(int pixels);//pixels is the distance from perpendicular
    int width,height;
protected:
    virtual vector<CameraObject> findObjects() = 0; //finds objects in pixel units
public:
    CameraObjectFinder(AxisCamera* ncamera);
    void update(); //updates the best object if there is a new camera image using findObjects(). converts to angle units.
    bool isObject(); //says if there is an object in the image good enough
    CameraObject getObject(); //returns best object
};

#endif
