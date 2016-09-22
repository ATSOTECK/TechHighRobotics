#include "SimpleControlSystem.h"

SimpleControlSystem::SimpleControlSystem()
{
	m_io = &DriverStation::GetInstance()->GetEnhancedIO();
	m_armjoy = new Joystick(JOYSTICK_ARM);
	m_hand = new HandControl(JOYSTICK_HAND);
}

double SimpleControlSystem::GetArmPosition()
{
	return m_armjoy->GetY();
}

int SimpleControlSystem::GetClawTop()
{
	return m_hand->getTop();
}

int SimpleControlSystem::GetClawBottom()
{
	return m_hand->getBottom();
}

bool SimpleControlSystem::GetMinibotDeploy()
{
	return m_io->GetDigital(MINIBOT_DEPLOY) || m_armjoy->GetRawButton(6);
}

bool SimpleControlSystem::GetMinibotShoot()
{
	return m_io->GetDigital(MINIBOT_SHOOT) || m_armjoy->GetRawButton(7);
}
