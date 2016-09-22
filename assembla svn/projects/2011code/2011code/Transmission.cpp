#include "Transmission.h"

Transmission::Transmission(Joystick *njoy,SinCosMagneticEncoder* _enc1,SinCosMagneticEncoder* _enc2,int pm1on,int pm1off,int pm2on,int pm2off)
{
	pm = new PneumaticsMechanism*[2];
	pm[0] = new PneumaticsMechanism(pm1on,pm1off,false);
	pm[1] = new PneumaticsMechanism(pm2on,pm2off,false);
	encoder1 = _enc1;
	encoder2 = _enc2;
	joy = njoy;
}

void Transmission::reset()
{
	pm[0]->Default();
	pm[1]->Default();
}

void Transmission::update()
{
	if(joy->GetTrigger()) {
		pm[0]->On();
		pm[1]->On();
		printf("slow");
	}
	else {
		pm[0]->Off();
		pm[1]->Off();
		printf("fast");
	}
	/*if(IsOn())
	{
		if((encoder1->GetRate() + encoder2->GetRate()) / 2 < SHIFTLIMIT_LOW)	Off();
	}
	else
	{
		if((encoder1->GetRate() + encoder2->GetRate()) / 2 > SHIFTLIMIT_HIGH)	On();
	}*/
}
