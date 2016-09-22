#include "Robotics675.h"
#include "Target.h"

class Target10Finder : public CameraObjectFinder {
protected:
    virtual void findObjects();
public:
    Target10Finder(AxisCamera *ncamera);
};
