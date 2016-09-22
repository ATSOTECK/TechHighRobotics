#include "WPIlib.h"
#include "../DriveTrain.h"
#include "../Arm.h"
#include "../CounterForce.h"

class Robot2011ArmTest : public SimpleRobot {
	AxisCamera *camera;
	ControlledJoint *arm;
	RobotDrive *drive;
	Joystick *rstick,*lstick;
	Jaguar *jag1,*jag2;
	//DigitalInput *testThingy;
	DigitalInput *a,*b;
	DriverStation *ds;
public:
	Robot2011ArmTest() {
		ds = DriverStation::GetInstance();
		rstick = new Joystick(1);
		arm = new ControlledJoint(new CounterForce,1,2,7);
		arm->setGearRatio(68/9);
		//drive = new RobotDrive(2,3);
	}
	void Disabled() {
		printf("disabled, this is the stupid arm test...\n");
	}
	void Autonomous() {
		printf("run teleop\n");
	}
	void OperatorControl() {
		while(1) {
			//arm->setTargetAngle(20);
			arm->setTargetAngle((int)(ds->GetAnalogIn(1)*10));
			arm->update();
			//drive->TankDrive(rstick,lstick);
			Wait(0.1);
		}
	}
};
//START_ROBOT_CLASS(Robot2011ArmTest);
