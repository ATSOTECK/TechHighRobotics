#include "TargetTracker.h"
#define SCORE 900

TargetTracker::TargetTracker() {	
	//gyro
	gyro = new Gyro(GYRO_PORT);
	gyro->SetSensitivity(0.007);
	//Output thingy
	turnValue = new PIDNumber();
	//camera
	AxisCamera *camera = &AxisCamera::GetInstance();
	camera->WriteResolution(AxisCamera::kResolution_320x240);
	camera->WriteCompression(20);
	camera->WriteBrightness(0);
	//retrofinder
	targetFinder = new RetroFinder(camera);
	//pidcontroller
	control = new PIDController(PID,gyro,turnValue,0.005);
	control->SetInputRange(-360.0, 360.0);
	control->SetOutputRange(-0.6, 0.6);
	control->SetTolerance(1.0 / 90.0 * 100);
	control->Enable();
}

bool TargetTracker::isTracking() {
	return isAllGood;
}

double TargetTracker::getTurnValue() {
	return turnValue->value;
}

void TargetTracker::update() {
	isAllGood = false;
	targetFinder->update();
	if(targetFinder->isObject()) 
	{
		CameraObject *obj = targetFinder->getObject();
		//printf("%f\n",obj->xAngle);
		double gyroAngle = gyro->PIDGet();
		double setPoint = gyroAngle + obj->xAngle;
		//printf("%f\n",setPoint);
		control->SetSetpoint(setPoint);
		if(obj->score > SCORE)
			isAllGood = true;
	}
	else 
	{
		//printf("nt\n");
	}
	Wait(.05);
}
