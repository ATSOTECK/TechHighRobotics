/*#ifndef MAGNETIC_ENCODER_H
#define MAGNETIC_ENCODER_H

#include "Includes.h"

class MagneticEncoder : public PIDSource {
public:
	MagneticEncoder(int port);
	virtual ~MagneticEncoder();
	//double encoder
	double getAngle();
	double getRate();
	void resetAngle();
	double PIDGet();
private:
	AnalogChannel *ana;
	AnalogTrigger *trigger1;
	Counter *counter;
};

#endif
*/