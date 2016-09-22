#include "ControlledJoint.h"

ControlledJoint::ControlledJoint(Function *staticJagValue,int encPortA,int encPortB,int jagPort) {
	staticValue = staticJagValue;
	jag = new Jaguar(jagPort);
	enc = new CoolEncoder(encPortA,encPortB);
	enc->SetReverseDirection(true);
	enc->Start();
	gearRatio = 1;
	t = new Timer();
	lasterror = 0;
	ds = DriverStation::GetInstance();
	lcd = DriverStationLCD::GetInstance();
	min = max = NULL;
}

void ControlledJoint::setGearRatio(double ratio) {
	gearRatio = ratio;
}

void ControlledJoint::setLimetSwitches(DigitalInput *mn,DigitalInput *mx) {
	min = mn;
	max = mx;
}

int ControlledJoint::getAngle() {
	return (int)enc->GetDistance();
}

void ControlledJoint::setTargetAngle(float angle) {
	target = angle;
}

bool ControlledJoint::onTarget() {
	if(fabs(target - lasterror/gearRatio) > MAX_ERROR)
		return true;
	return false;
}

void ControlledJoint::update() {
	
	double angle = enc->GetDistance()/gearRatio;
	double error = target - angle;
	double rate = enc->GetCoolRate();
	double value = error*0.02/* - rate*0.01 + staticValue->get(angle)*/;
	lasterror = error;
	if(value > .4)value = .4;
	if(value < -.4)value = -.4;
	if(min != NULL)
		if(min->Get() && value < 0) {
			value = 0;
			enc->Reset();
		}
	if(max != NULL)
		if(max->Get() && value > 0) {
			value = 0;
		}
	printf("a:%6.1f e:%6.1f v:%8.1f m = %6.2f",angle,error,rate,value);
	//lcd->UpdateLCD();
	jag->Set(value);
}
