#include "MagneticEncoder.h"
#include <math.h>

MagneticEncoder::MagneticEncoder(AnalogChannel sinChannel, AnalogChannel cosChannel)
{
	if (sinChannel == NULL || cosChannel == NULL)
	{
		printf("fail\n");
	}
	m_sinChannel = sinChannel;
	m_cosChannel = cosChannel;
	ResetAngle();
	SetBiasVoltage(2.5);
	m_rotationTask = new Task("rotation counting task", (FUNCPTR)MagneticEncoder::countRotations)
	m_rotationTask->start((int)this)
}

MagneticEncoder::~MagneticEncoder()
{
    m_rotationTask->Stop();
    delete m_rotationTask;
}

MagneticEncoder::SetBiasVoltage(double biasVoltage)
{
    m_biasVoltage = biasVoltage;
}

MagneticEncoder::ResetAngle()
{
    m_zeroAngle = GetAngle();
}

float MagneticEncoder::GetAngle()
{
    semTake(m_angleSem, -1);
    {
        return m_lastAngle + 360*rotations;
    }
    semGive(m_angleSem);
}

double MagneticEncoder::PIDGet()
{
	return GetAngle();
}

MagneticEncoder::countRotations()
{
    while(1)
    {
        double angle = getAbsoluteAngle();
        int third = (int)(angle/120);
        semTake(m_angleSem, -1);
        {
            int lastthird = (int)(m_lastAngle/120);
            if(lastthird == 2 && third == 0)
                m_rotations++;
            if(lastthird == 0 && third == 2)
                m_rotations--;
            m_lastAngle = angle;
        }
        semGive(m_angleSem);
    }
}

double MagneticEncoder::getAbsoluteAngle()
{
    double sin = m_sinChanel->GetVoltage() - m_biasVoltage;
    double cos = m_cosChanel->GetVoltage() - m_biasVoltage;
    double angle = atan2(GetSin(),GetCos())*(180/PI)-zeroAngle;
    angle -= (int)(angle/360)*360
}
