#ifndef MULTIPLEX_H
#define MULTIPLEX_H

#include "Includes.h"

class MultiplexedRotarySwitch {
	DriverStation *ds;
	bool inverted;
	DriverStationEnhancedIO *m_io;
public:
	MultiplexedRotarySwitch() {
		ds = DriverStation::GetInstance();
		m_io = &DriverStation::GetInstance()->GetEnhancedIO();
		
	}
	void setInverted(bool inv) {
		inverted = inv;
	}
	bool getChannel(int ch) {
		m_io->SetDigitalOutput(1,(ch/1) % 2); //black
		m_io->SetDigitalOutput(2,(ch/2) % 2); //red
		m_io->SetDigitalOutput(3,(ch/4) % 2); //white
		Wait(.005);
		return inverted ? !m_io->GetDigital(4) : m_io->GetDigital(4);
	}
};

#endif
