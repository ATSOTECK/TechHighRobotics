#include "Target10finder.h"

Target10Finder::Target10Finder(AxisCamera* ncamera) : CameraObjectFinder(ncamera){
}

CameraObject* Target10Finder::findObject(ColorImage *image) {
    vector<Target> targets = Target::FindCircularTargets(image);
	if(targets.size() == 0 || targets[0].m_score < .01)
	   return NULL;
	else {
	    CameraObject *best = new CameraObject;
        best->xAngle = targets[0].m_xPos;
        best->yAngle = targets[0].m_yPos;
        best->size = targets[0].m_majorRadius*2;
        return best;
    }
}
