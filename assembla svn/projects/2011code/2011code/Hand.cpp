#include "Hand.h"
#include "ports.h"

Hand::Hand() {
	joy = new Joystick(4);
	//topm = new Relay(HAND_TOP_MOTOR,Relay::kBothDirections);
	//botm = new Relay(HAND_BOTTOM_MOTOR,Relay::kBothDirections);
	t = new Timer();
	t->Stop();
}

void Hand::update(int _top,int _bottom) {
	if(joy->GetRawButton(1))
	{
		_top = 1; 
		_bottom = 1;
	}
	else if(joy->GetRawButton(3))
	{
		_top = -1; 
		_bottom = -1;
	}
	else if(joy->GetRawButton(4))
	{
		_top = 1;
		_bottom = -1;
	}
	else if(joy->GetRawButton(5))
	{
		_top = -1;
		_bottom = 1;
	}
	else
	{
		_top = 0; 
		_bottom = 0;
	}
	_top = -_top;
	if(_top == 1) topm->Set(Relay::kForward);
	else if(_top == 0) topm->Set(Relay::kOff);
	else if(_top == -1) topm->Set(Relay::kReverse);
	
	if(_bottom == 1) botm->Set(Relay::kForward);
	else if(_bottom == 0) botm->Set(Relay::kOff);
	else if(_bottom == -1) botm->Set(Relay::kReverse);
	printf("hand(%d,%d)",_top,_bottom);
	
	//or not
	/*
	if(t->Get() < ROTATE_FORWARD_TIME) {
		topm->Set(Relay::kReverse); //rotate forward
		botm->Set(Relay::kForward);
	}
	else if(t->Get() < RELEASE_TIME + ROTATE_FORWARD_TIME) {
		topm->Set(Relay::kForward); //eject
		botm->Set(Relay::kForward);
	}
	else {
		if (!isback->Get()) {
			topm->Set(Relay::kReverse); //suck in
			botm->Set(Relay::kReverse);
		}
		else if (!isup->Get()) {
			topm->Set(Relay::kForward); //rotate back
			botm->Set(Relay::kReverse);
		}
	}*/
}

void Hand::release() {
	topm->Set(Relay::kReverse);
	botm->Set(Relay::kForward);
	printf("releasing");
}
