#include "WPIlib.h"
#include "../DriveTrain.h"
#include "../SinCosMagneticEncoder.h"

class Robot2011AmTest : public SimpleRobot {
	RobotDrive *drive;
	Joystick *rstick,*lstick;
	Jaguar *jag1,*jag2;
	DriverStation *ds;
	SinCosMagneticEncoder* me;
public:
	Robot2011AmTest() {
		ds = DriverStation::GetInstance();
		drive = new RobotDrive(2,3);
		me = new SinCosMagneticEncoder(3,4);
		//me->SetBiasVoltage(2.25);
	}
	void Disabled() {
		printf("disabled, mag enc...\n");
	}
	void Autonomous() {
		printf("run teleop\n");
	}
	void OperatorControl() {
		while(1) {
			printf("abs angle: %f   \tcount: %f   \trate: %f\n",me->getAbsoluteAngle(),me->GetAngle(),me->GetRate());
			Wait(0.1);
		}
	}
};
//START_ROBOT_CLASS(Robot2011AmTest);
