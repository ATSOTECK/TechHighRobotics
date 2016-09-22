#ifndef SIMPLE_CONTROL_SYSTEM
#define SIMPLE_CONTROL_SYSTEM

#include "Includes.h"
#include "ControlBase.h"
#include "HandControl.h"

class SimpleControlSystem : public ControlBase
{
	DriverStationEnhancedIO* m_io;
	Joystick* m_armjoy;
	HandControl* m_hand;
public:
	SimpleControlSystem();
	
	double GetArmPosition();
	int GetClawTop();
	int GetClawBottom();
	bool GetMinibotDeploy();
	bool GetMinibotShoot();
};

#endif
