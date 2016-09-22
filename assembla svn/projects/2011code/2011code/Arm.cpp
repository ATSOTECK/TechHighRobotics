#include "Arm.h"
#include "Jaguar.h"
#include "ports.h"
#include "CounterForce.h"

Arm::Arm() {
	motors = new Jaguar(ARM_MOTOR);
	joystick = new Joystick(JOYSTICK_ARM);
	hand = new Hand;
	armUp = new DigitalInput(ARM_ISUP);
	armDown = new DigitalInput(ARM_ISDOWN);
	joint = new ControlledJoint(new CounterForce,ARM_ENC_A,ARM_ENC_B,ARM_MOTOR);
	joint->setLimetSwitches(armDown,armUp);
	ds = DriverStation::GetInstance();
}

void Arm::setAngle(double a) {
	joint->setTargetAngle(a);
}

void Arm::update(int _top,int _bottom) {
	//joint->update();
	double value = joystick->GetY();
	/*if(armDown != NULL)
	{
		if(value < 0 && armDown->Get())
			value = 0;
	}*/
	if(armUp != NULL)
	{
		if(value > 0 && armUp->Get())
			value = 0;
	}
	if(value < 0) {
		value = value * .20;
	}
	motors->Set(-value);
	//hand->update(_top,_bottom);
	printf("Value: %f LmtSwchs: %d %d",value,armDown->Get(),armUp->Get());
}
 
bool Arm::onTarget() {
	return joint->onTarget();
}

void Arm::autoupdate() {
	if(armUp->Get()) {
		motors->Set(0);
	}
	else {
		motors->Set(-0.8);
	}
	printf(" autoupdate ls:%d",armUp->Get());
}
