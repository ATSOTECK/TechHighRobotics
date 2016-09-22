#include "MinibotDeploy.h"
#include "Includes.h"

#define MIN_DEPLOY_ANGLE servo1->GetMaxAngle()
#define MAX_DEPLOY_ANGLE MIN_DEPLOY_ANGLE - 120
#define MIN_SHOOT_ANGLE servo2->GetMaxAngle() - 50
#define MAX_SHOOT_ANGLE MIN_SHOOT_ANGLE - 40

#define MINIBOT_BUTTON 4
//#define RELEASE_THE_KRAKEN_TIME 254 //LOL CHEEZY

MinibotDeploy::MinibotDeploy() {
	joy = new Joystick(3);
	servo1 = new Servo(MINIBOT_SERVO_1);
	servo2 = new Servo(MINIBOT_SERVO_2);
	t = new Timer();
	t->Start();
	servo1->Set(MIN_DEPLOY_ANGLE);
	servo2->Set(MIN_SHOOT_ANGLE);
}

void MinibotDeploy::update(bool _deploy,bool _shoot) {
	if(_deploy)
		servo1->SetAngle(MAX_DEPLOY_ANGLE);
	else
		servo1->SetAngle(MIN_DEPLOY_ANGLE);
	if (_shoot)
		servo2->SetAngle(MAX_SHOOT_ANGLE);
	else
		servo2->SetAngle(MIN_SHOOT_ANGLE);
	printf("SERVOS: (d:%d,s:%d)",_deploy,_shoot);
}
