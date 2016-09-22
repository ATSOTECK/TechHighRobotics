#ifndef HANDCONTROL_H
#define HANDCONTROL_H

#include "Includes.h"

class HandControl : public Joystick
{
	int m_top,m_bottom;
	DriverStationEnhancedIO* m_io;
public:
	HandControl(int _port);
	
	void update();
	int getTop();
	int getBottom();
};

#endif
