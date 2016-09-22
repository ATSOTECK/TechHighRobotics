#include "WPIlib.h"

class Robot2011I2CTest : public SimpleRobot {

public:
	Robot2011I2CTest() {
	}
	void Disabled() {
		printf("disabled, this is the arg servo thing...\n");
	}
	void Autonomous() {
		Servo release(10);
		Servo deploy(9);
		while(1) {
				printf("%f %f\n",release.Get(),deploy.Get());
				Wait(0.5); // wait 1 second
			}
		}

	void OperatorControl() {
	}
};
//START_ROBOT_CLASS(Robot2011I2CTest);
