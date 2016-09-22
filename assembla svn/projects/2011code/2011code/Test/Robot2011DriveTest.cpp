#include "WPIlib.h"
#include "../DriveTrain.h"

class Robot2011DriveTest : public SimpleRobot {
	//RobotDrive *drive;
	Joystick *joy;
	Jaguar* jag1,*jag2;
	DriverStation *ds;
	DriveTrain *drive;

public:
	Robot2011DriveTest() {
		ds = DriverStation::GetInstance();
		jag1 = new Jaguar(3);
		jag2 = new Jaguar(4);
		// = new RobotDrive(jag1,jag2);
		drive = new DriveTrain();
	}
	void Disabled() {
		printf("disabled, this is the stupid arm test...\n");
	}
	void Autonomous() {
		printf("run teleop\n");
		while(1) 
		{
			drive->teleupdate();
			printf("jag1: %f\t\tjag2: %f\n",jag1->Get(),jag2->Get());
		}
	}
	void OperatorControl() {
		while(1) {
			drive->teleupdate();
			Wait(0.1);
		}
	}
};
//START_ROBOT_CLASS(Robot2011DriveTest);

