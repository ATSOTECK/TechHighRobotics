#define CONTROL_COMPLEX   false

#include "Includes.h"
#include "DriveTrain.h"
#include "Arm.h"
#include "MinibotDeploy.h"
#include "ControlBase.h"
#include "ControlSystem.h"
#include "SimpleControlSystem.h"

class Robot2011 : public SimpleRobot {
	DriveTrain* drive;
	Arm* arm;
	MinibotDeploy *minibot;
	DriverStation *ds;
	Timer *t;
	ControlBase* control;
	Relay* topm;
	Relay* botm;
	Joystick* joy;
public:
	Robot2011();
	
	void Disabled();
	void Autonomous();
	void OperatorControl();
};
START_ROBOT_CLASS(Robot2011);
