#include "WPIlib.h"
#include "../RotarySwitch.h"

class Robot2011IOTest : public SimpleRobot {
	DriverStation *ds;
	DriverStationEnhancedIO* io;
	RotarySwitch *rs;
public:
	Robot2011IOTest() {
		ds = DriverStation::GetInstance();
		io = &ds->GetEnhancedIO();
		rs = new RotarySwitch();
	}
	void Disabled() {
		printf("disabled, this is the IO test...\n");
	}
	void Autonomous() {
		printf("run teleop\n");
	}
	void OperatorControl() {
		while(ds->IsOperatorControl()) {
			printf("%d",rs->GetState());
			Wait(0.5);
			printf("\n");
		}
	}
};
//START_ROBOT_CLASS(Robot2011IOTest);
