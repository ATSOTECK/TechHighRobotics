#ifndef ARM_H
#define ARM_H

#include "Includes.h"
#include "ControlledJoint.h"
#include "Hand.h"

//arm length and position first joint TODO: measure
#define LENGTH //from joint to center of claw
#define X1 //relative to front of robot
#define Y1 //relative to ground

#define MAX_ANGLE 130 //reletive to START_ANGLE TODO: record angles
#define START_ANGLE 20 //folded up angle relative to pointing directly down

class Arm {
protected:
	ControlledJoint *joint;
	DigitalInput *armDown, *armUp;
	Joystick *joystick;
	DriverStation *ds;
	Jaguar *motors;//testing only
public:
	Arm();
	void setAngle(double a);
	bool onTarget();
	void update(int _top,int _bottom);
	void autoupdate();
	Hand *hand;
};

#endif
