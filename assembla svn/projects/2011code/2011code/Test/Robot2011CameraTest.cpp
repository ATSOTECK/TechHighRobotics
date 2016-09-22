#include "WPIlib.h"
#include "../DriveTrain.h"
#include "../Arm.h"
#include "../TargetTracker.h"

class Robot2011Test : public SimpleRobot {
	RobotDrive* base;
	TargetTracker* tracker;
public:
	Robot2011Test() 
	{
		base = new RobotDrive(1,2,3,4);
		tracker = new TargetTracker;
	}
	
	void Disabled() 
	{
		printf("disabled, this is the amaizing camera test...\n");
	}
	
	void Autonomous() 
	{
		printf("run teleop\n");
	}
	
	void OperatorControl()
	{
		while(IsOperatorControl()) 
		{
			tracker->update();
			base->ArcadeDrive(0,(float) tracker->getTurnValue());
			Wait(.05);
		}
	}
}; 
//jkSTART_ROBOT_CLASS(Robot2011Test);
