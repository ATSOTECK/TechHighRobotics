#include "DriveTrain.h"
#define DEGREES_PER_FOOT 226
#define AUTO_DIST		 13.5
#define AUTO_P			 1.0

DriveTrain::DriveTrain() {
	jag1 = new Jaguar(DRIVE_LEFT_MOTOR);
	jag2 = new Jaguar(DRIVE_RIGHT_MOTOR);
	drive = new RobotDrive(jag1,jag2);
	drive->SetInvertedMotor(RobotDrive::kRearLeftMotor,true);
	drive->SetInvertedMotor(RobotDrive::kRearRightMotor,true);
	linefollower = new LineSensor(11,4);
	encoder = new CoolEncoder(DRIVE_ENC_A,DRIVE_ENC_B);
	encoder->SetReverseDirection(true);
	encoder->Start();
	ljoy = new Joystick(L_JOYSTICK_DRIVE);
	rjoy = new Joystick(R_JOYSTICK_DRIVE);
	tank = true;
	inA = new DigitalInput(DRIVE_ENC_A);
	inB = new DigitalInput(DRIVE_ENC_B);
	ds = DriverStation::GetInstance();
	home = 0;
}

void DriveTrain::reset()
{
	home = getDistanceTraveled();
	//transmission->reset();
	//encoder1->ResetAngle();
	//encoder2->ResetAngle();
	//home = getDistanceTraveled();
}

void DriveTrain::autoupdate(float time) {
	if(time > 14.6) {
		drive->ArcadeDrive(.5,linefollower->getTurnValue(.2));
	}
	else {
		float move;
		if(getDistanceTraveled() < AUTO_DIST)
			move = -.45;
		else
			move = .2;
		if(linefollower->isLine()) {
			printf("|dist:%9.2f move:%f|(%d,%d)",getDistanceTraveled(),move,inA->Get(),inB->Get());
			drive->ArcadeDrive(move,linefollower->getTurnValue(.2));
		}
		else
			printf("noline");
	}
}

void DriveTrain::teleupdate() {
	//cam->update();
	
	if(rjoy->GetTrigger()) {
		drive->TankDrive(ljoy->GetY()*.5,rjoy->GetY()*.5);
	} 
	else {
		//Boring Tank Drive
		drive->TankDrive(ljoy,rjoy);
		
	}
	//254 Drive
	//if(rjoy->GetTrigger()) drive->ArcadeDrive(0.0,rjoy->GetX(),false);
	//else drive->ArcadeDrive(-ljoy->GetY(),rjoy->GetX() * -ljoy->GetY(),false);
	printf("drive:(%5.2f,%5.2f) ",jag1->Get(),jag2->Get());
	
}
float DriveTrain::getDistanceTraveled(){
	return (float)encoder->Get()/DEGREES_PER_FOOT - home;
}

