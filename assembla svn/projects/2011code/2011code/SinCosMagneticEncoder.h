#ifndef MAGNETIC_ENCODER_H_
#define MAGNETIC_ENCODER_H_

#include "Includes.h"

class SinCosMagneticEncoder : public PIDSource {
public:
	SinCosMagneticEncoder(int portA, int portB);
	virtual ~SinCosMagneticEncoder();

	double GetAngle();
	double GetRate();
	void ResetAngle();
	void SetBiasVoltage(double biasVoltage);
	double PIDGet();
	double getAbsoluteAngle();
private:
	AnalogChannel *m_sinChannel, *m_cosChannel;
	Counter *rotations;
	float m_biasVoltage;
	Timer *m_time;
	double m_prevdist,m_prevtime;
};

#endif
