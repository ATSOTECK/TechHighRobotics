#include "Includes.h"
#include "Pneumatics.h"

class MinibotDeploy {
	Servo *servo1, *servo2;
	Timer *t;
	Joystick *joy;
public:
	MinibotDeploy();
	void update(bool _deploy,bool _shoot);
};
