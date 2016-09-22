#include "CameraObjectFinder.h"
#include "Target.h"

class Target10Finder : public CameraObjectFinder {
protected:
    virtual CameraObject *findObject(ColorImage* image);
public:
    Target10Finder(AxisCamera *ncamera);
};
