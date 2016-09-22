#include "WPIlib.h"
#include "../Includes.h"
#include "../LineSensor.h"

#define SPEED 0

class Robot2011LineTest : public SimpleRobot {
	LineSensor *ls;
	DriverStation *ds;
	RobotDrive *drive;
	Joystick *joy;
public:
	Robot2011LineTest() {
		ls = new LineSensor(LINE_SENSOR,4);
		ds = DriverStation::GetInstance();
		drive = new RobotDrive(1,2);
		joy = new Joystick(1);
		drive->SetExpiration(.1);
	}
	void Disabled() {
		printf("disabled, this is the line test.\n");
	}
	void Autonomous() {
		while(ds->IsAutonomous()) {
			double turn = ls->getTurnValue(1);
			Wait(.08);
			printf("turn: %f",turn);
			//drive->ArcadeDrive(SPEED,turn,false);
			//printf ("left: %d middle: %dright: %d " digital );
		}
	}
	void OperatorControl() {
		while(ds->IsOperatorControl()) {
			drive->ArcadeDrive(joy);
			Wait(.08);
			printf("%f\n",joy->GetY());
		}
	}
};
//START_ROBOT_CLASS(Robot2011LineTest);
