#ifndef COOL_ENCODER_H
#define COOL_ENCODER_H

#include "Includes.h"

class CoolEncoder : public Encoder
{
	Timer* m_time;
	double m_prevdist,m_prevtime;
public:
	CoolEncoder(UINT32 _aChannel, UINT32 _bChannel);
	double GetCoolRate(); //you need to call often to get good results.
};

#endif
