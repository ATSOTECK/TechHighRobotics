#include "CoolEncoder.h"

CoolEncoder::CoolEncoder(UINT32 _aChannel, UINT32 _bChannel) : Encoder(_aChannel,_bChannel) {
	m_time = new Timer;
	m_prevdist = m_prevtime = 0;
	m_time->Start();
}

double CoolEncoder::GetCoolRate()
{
	double t_result = (GetDistance() - m_prevdist) / (m_time->Get() - m_prevtime);
	m_prevdist = GetDistance();
	m_prevtime = m_time->Get();
	return t_result;
}
