#include "Includes.h"
#include "ports.h"
#include "Pneumatics.h"
#include "SinCosMagneticEncoder.h"

#define SHIFTLIMIT_HIGH 5
#define SHIFTLIMIT_LOW 3

class Transmission
{
protected:
	PneumaticsMechanism** pm;
	SinCosMagneticEncoder* encoder1,*encoder2;
	Joystick *joy;
public:
	Transmission(Joystick* njoy,SinCosMagneticEncoder* _enc1,SinCosMagneticEncoder* _enc2,int pm1on,int pm1off,int pm2on,int pm2off);
	
	void reset();
	void update();
};
