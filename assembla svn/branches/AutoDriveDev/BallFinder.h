#include "Robotics675.h"

class BallFinder : public CameraObjectFinder {
protected:
    virtual void findObjects();
public:
    BallFinder(AxisCamera *ncamera);
};
