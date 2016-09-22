#include "BallFinder.h"

BallFinder::BallFinder(AxisCamera* ncamera) : CameraObjectFinder(ncamera){
}

CameraObject Target10Finder::findObject(ColorImage *image) {
    BinaryImage* binImg = image->thresholdHSL(0,255,0,255,200,255);//just guesses at good values
	vector<ParticleAnalysisReport>* blobs = binImg->GetOrderedParticleAnalysisReports();
	//... find a good blob
    CameraObject* best;
    //... make it a CameraObject
    return best;
}
