#ifndef MAGNETIC_ENCODER_H_
#define MAGNETIC_ENCODER_H_

#include "AnalogChannel.h"
#include "PIDSource.h"
#include "Task.h"

class MagneticEncoder : public PIDSource {
public:
	MagneticEncoder(AnalogChannel *m_sinChannel, AnalogChannel *m_sinChannel);
	virtual ~MagneticEncoder();

	double GetAngle();
	void ResetAngle();
	void SetBiasVoltage();
	double PIDGet();
	
private:
	AnalogChannel *m_sinChannel, *m_cosChannel;
	float m_biasVoltage;
	int m_rotations;
	double m_lastAngle;
	double m_zeroAngle;
	
	Task *m_rotationTask;
	SEM_ID m_angleSem;
	
	void countRotations();
	double getAbsoluteAngle();
};

#endif
