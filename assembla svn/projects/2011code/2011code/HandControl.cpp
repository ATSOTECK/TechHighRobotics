#include "HandControl.h"

HandControl::HandControl(int _port) : Joystick(_port)
{
	m_top = m_bottom = 0;
	m_io = &DriverStation::GetInstance()->GetEnhancedIO();
}

void HandControl::update()
{
	if(GetRawButton(1)) {
		m_top = 1;
		m_bottom = 1;
	}
	else if(GetRawButton(2)) {
		m_top = -1;
		m_bottom = -1;
	}
	else if(GetY() < -0.2) {
		m_top = 1;
		m_bottom = -1;
	}
	else if(GetY() > 0.2) {
		m_top = -1;
		m_bottom = 1;
	}
	else {
		m_top = 0;
		m_bottom = 0;
	}

	printf("hand(%d,%d)",m_top,m_bottom);
	
}

int HandControl::getTop()
{
	return m_top;
}

int HandControl::getBottom()
{
	return m_bottom;
}
