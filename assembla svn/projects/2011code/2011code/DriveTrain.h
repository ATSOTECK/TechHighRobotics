#include "Includes.h"
#include "LineSensor.h"
#include "TargetTracker.h"
#include "Transmission.h"
#include "CoolEncoder.h"

#define SPACING_FRONT 2
#define SPACING_BACK 2

class DriveTrain
{
protected:
	RobotDrive *drive;
	LineSensor *linefollower;
	CoolEncoder *encoder;//,*encoder2; 
	//Transmission *transmission;
	Joystick *rjoy, *ljoy;
	bool tank;
	//TargetTracker *cam;
	Jaguar* jag1,*jag2;
	DriverStation *ds;
	DigitalInput *inA,*inB;
	float home;
public:
	DriveTrain();
	void reset();
	void autoupdate(float time);
	void teleupdate();
	float getDistanceTraveled();
};
