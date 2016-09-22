#include "SinCosMagneticEncoder.h"

SinCosMagneticEncoder::SinCosMagneticEncoder(int portA,int portB)
{
	m_biasVoltage = 2.25;
	m_cosChannel = new AnalogChannel(portA);
	m_sinChannel = new AnalogChannel(portB);
	AnalogTrigger *trigger1 = new AnalogTrigger(m_sinChannel);
	AnalogTrigger *trigger2 = new AnalogTrigger(m_cosChannel);
    trigger1->SetLimitsVoltage(m_biasVoltage-.01,m_biasVoltage+.01);
    trigger2->SetLimitsVoltage(m_biasVoltage-.01,m_biasVoltage+.01);
	rotations = new Counter(Counter::k2X,trigger1->CreateOutput(AnalogTriggerOutput::kState),
			trigger2->CreateOutput(AnalogTriggerOutput::kState),false);
	//rotations->SetUpSource(trigger1->CreateOutput(AnalogTriggerOutput::kState));
	//rotations->SetDownSource(trigger2->CreateOutput(AnalogTriggerOutput::kState));
	//rotations->SetReverseDirection(true);
	rotations->Start();
	ResetAngle();
	m_time = new Timer;
	m_prevdist = m_prevtime = 0;
	m_time->Start();
}

SinCosMagneticEncoder::~SinCosMagneticEncoder()
{
    delete rotations;
}

void SinCosMagneticEncoder::SetBiasVoltage(double biasVoltage)
{
    m_biasVoltage = biasVoltage;  //biasVoltage;
}

void SinCosMagneticEncoder::ResetAngle()
{
    rotations->Reset();
}

double SinCosMagneticEncoder::GetAngle()
{ 
    return floor(rotations->Get()/2.0) * 360 + getAbsoluteAngle();
}

double SinCosMagneticEncoder::GetRate() {
	double t_result = (GetAngle() - m_prevdist) / (m_time->Get() - m_prevtime);
	m_prevdist = GetAngle();
	m_prevtime = m_time->Get();
	return t_result;
}

double SinCosMagneticEncoder::PIDGet()
{
	return GetAngle();
}

double SinCosMagneticEncoder::getAbsoluteAngle()
{
    double sin = m_sinChannel->GetVoltage() - m_biasVoltage;
    double cos = m_cosChannel->GetVoltage() - m_biasVoltage;
    printf(" sin:%5.2f  cos:%5.2f  count:%5.2f",
    		m_sinChannel->GetVoltage(),m_cosChannel->GetVoltage(),floor(rotations->Get()/2.0));
    double angle = atan2(sin,cos)*(180/3.1415928353);
    return angle + 180;
}
