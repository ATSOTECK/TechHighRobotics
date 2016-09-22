#ifndef TRACKER_H
#define TRACKER_H

#include "Includes.h"
#include "RetroFinder.h"
#include "ports.h"

#define PID .1,0,0

class PIDNumber : public PIDOutput {
public:
	double value;
	void PIDWrite(float newValue) {
		value = newValue;
	}
};

class TargetTracker
{
protected:
	Relay *fs;
	CameraObjectFinder *targetFinder;
	PIDController *control;
	PIDNumber *turnValue;
	Gyro *gyro;
	bool isAllGood;
public:
	TargetTracker();
	double getTurnValue();
	void update();
	bool isTracking();
};

#endif
