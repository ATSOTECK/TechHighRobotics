/*#include "ArmControl.h"

ArmControl::ArmControl()
{
	m_io = &DriverStation::GetInstance()->GetEnhancedIO();
	m_position = 0;
}

void ArmControl::update()
{
	if(m_io->GetDigital(ARM_INCREMENT) && m_position < 7) m_position++;
	if(m_io->GetDigital(ARM_DECREMENT) && m_position > 0) m_position--;
	
	for(int a = 0;a < 8;a++)
	{
		if(a == m_position) m_io->SetDigitalOutput(ARM_LED + a,true);
		else m_io->SetDigitalOutput(ARM_LED + a,false);
	}
}

int ArmControl::get()
{
	return m_position;
}
*/
