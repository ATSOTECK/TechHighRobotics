#ifndef RETRO_H
#define RETRO_H

#include "Includes.h"
#include "CameraObjectFinder.h"
#include "vector"

class RetroFinder : public CameraObjectFinder
{
	vector<ParticleAnalysisReport>* m_targets;
	float getDistance(double angle1, double angle2);
	ParticleAnalysisReport* findCenter();
	void findBottomTwo(int x,int maxError,ParticleAnalysisReport **_rep1,ParticleAnalysisReport **_rep2);
public:
	RetroFinder(AxisCamera *cam);
	virtual CameraObject* findObject(ColorImage *image);
};

#endif
