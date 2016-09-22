/*#include "MagneticEncoder.h"

MagneticEncoder::MagneticEncoder(int port) {
	ana = new AnalogChannel(port);
	trigger1 = new AnalogTrigger(ana);
	trigger1->SetLimitsVoltage(2,3);
	counter = new Counter(trigger1);
	counter->Start();
	printf("lena is awesome");
}

MagneticEncoder::~MagneticEncoder() {
	delete ana;
	delete counter; 
	delete trigger1;
}

double MagneticEncoder::getAngle() {
	int rotations = counter->Get();
	double voltage = ana->GetVoltage();
	double angle = rotations*160 + voltage*72;
	printf("%d \t\t %f \t\t %f\n",rotations,voltage,angle);
	return rotations*160 + voltage*72; // 72 is degrees per volt
}

double MagneticEncoder::getRate() {
	printf("%d %f\n",trigger1->GetTriggerState(),ana->GetVoltage());
	return counter->GetPeriod();
	
}

double MagneticEncoder::PIDGet() {
	return getAngle();
}

void MagneticEncoder::resetAngle() {
	counter->Reset();
}
*/
