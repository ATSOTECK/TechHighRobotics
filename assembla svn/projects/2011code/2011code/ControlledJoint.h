#ifndef CONTROLLEDJOINT_H
#define CONTROLLEDJOINT_H

#include "WPIlib.h"
#include "Function.h"
#include "CoolEncoder.h"

#define MAX_ERROR 2 //one degree

class ControlledJoint {
private:
	CoolEncoder *enc;
	Jaguar *jag;
	DigitalInput *min,*max;
	Function *staticValue; //says the moter value required for a specific angle to keep the joint static
	Timer *t;
	DriverStation *ds;
	DriverStationLCD *lcd;
	float target;
	double gearRatio;
	double lasterror;
public:
	ControlledJoint(Function *ef,int encPortA,int encPortB,int jagPort);
	void setExternalForce(Function *ef);
	void setLimetSwitches(DigitalInput *min,DigitalInput *max);
	void setGearRatio(double ratio);
	int getAngle();
	void setTargetAngle(float angle);
	void update();
	bool onTarget();
};

#endif
