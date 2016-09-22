#ifndef CONTROL_SYSTEM
#define CONTROL_SYSTEM

#include "Includes.h"
#include "ControlBase.h"
#include "RotarySwitch.h"
#include "HandControl.h"

#define ARM_JOYSTICK_SENSITIVITY	5

//useful positions TODO: record positions
#define NUM_ANGLES 8
const int angles[NUM_ANGLES] = {10,20,30,40,50,60,70,100};

class ControlSystem : public ControlBase
{
	DriverStation* m_ds;
	DriverStationEnhancedIO* m_io;
	RotarySwitch* m_rot;
	Joystick* m_armjoy;
	HandControl* m_hand;
public:
	ControlSystem();
	void LEDSet(int _port,bool _on);
	bool LEDGet(int _port);
	
	double GetArmPosition();
	int GetClawTop();
	int GetClawBottom();
	bool GetMinibotDeploy();
	bool GetMinibotShoot();
};

#endif
