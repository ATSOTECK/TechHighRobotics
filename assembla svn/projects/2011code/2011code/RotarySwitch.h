#ifndef ROTARY_SWITCH_H
#define ROTARY_SWITCH_H

#include "Includes.h"

class RotarySwitch
{
	DriverStationEnhancedIO *m_io;
public:
	RotarySwitch() {
		m_io = &DriverStation::GetInstance()->GetEnhancedIO();
	}
	
	int GetState() {
		for(int a = 0;a < 8;a++) {
			if(m_io->GetDigital(a+1)) return a;
		}
		return -1;
	}
};

#endif
