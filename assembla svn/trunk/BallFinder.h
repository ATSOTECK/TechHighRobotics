#include "Robotics675.h"

class BallFinder : public CameraObjectFinder {
protected:
    virtual void findObject();
public:
    BallFinder(AxisCamera *ncamera);
};
