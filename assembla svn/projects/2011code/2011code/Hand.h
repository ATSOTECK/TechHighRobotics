#ifndef HAND_H
#define HAND_H

#include "Includes.h"

#define ROTATE_FORWARD_TIME 1.0
#define RELEASE_TIME 1.0

class Hand
{
protected:
	Joystick* joy;
	DigitalInput *isup,*isback; //limet switches or light sensors that sense the tube
	Relay *topm,*botm; //top and bottom motors
	Timer *t; //time since last release
	Joystick *joystick;
public:
	Hand();
	void update(int _top,int _bottom); //call often
	void release(); //call to release tube
};

#endif
