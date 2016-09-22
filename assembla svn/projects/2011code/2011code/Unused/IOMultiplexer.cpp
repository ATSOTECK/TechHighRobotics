/*#include "IOMultiplexer.h"

IOMultiplexer::IOMultiplexer(int _in,int _out1,int _out2,int _out3) 
{
	m_io = &DriverStation::GetInstance()->GetEnhancedIO();
	m_in = _in;
	m_out1 = _out1;
	m_out2 = _out2;
	m_out3 = _out3;
}

bool IOMultiplexer::Get(int ch)
{
	m_io->SetDigitalOutput(m_out1,(ch/1) % 2);
	m_io->SetDigitalOutput(m_out2,(ch/2) % 2);
	m_io->SetDigitalOutput(m_out3,(ch/4) % 2);
	Wait(.005);
	return m_io->GetDigital(m_in);
}
*/
