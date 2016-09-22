#include "ControlSystem.h"

ControlSystem::ControlSystem()
{
	m_ds = DriverStation::GetInstance();
	m_io = &m_ds->GetEnhancedIO();
	m_rot = new RotarySwitch();
	m_armjoy = new Joystick(JOYSTICK_ARM);
	m_hand = new HandControl(JOYSTICK_HAND);
}

void ControlSystem::LEDSet(int _port,bool _on){
	m_io->SetDigitalOutput(_port,_on);
}

bool ControlSystem::LEDGet(int _port){
	return m_io->GetDigital(_port);
}

double ControlSystem::GetArmPosition(){
	return angles[m_rot->GetState()] + m_armjoy->GetY() * ARM_JOYSTICK_SENSITIVITY;
}

int ControlSystem::GetClawTop(){
	return m_hand->getTop();
}

int ControlSystem::GetClawBottom(){
	return m_hand->getBottom();
}

bool ControlSystem::GetMinibotDeploy(){
	return m_armjoy->GetRawButton(8);
}

bool ControlSystem::GetMinibotShoot(){
	return m_io->GetDigital(MINIBOT_SHOOT);
}
