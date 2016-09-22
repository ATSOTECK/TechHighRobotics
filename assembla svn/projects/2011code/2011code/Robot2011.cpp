#include "Robot2011.h"

Robot2011::Robot2011() {
	drive = new DriveTrain();
	arm = new Arm();
	minibot = new MinibotDeploy();
	ds = DriverStation::GetInstance();
	t = new Timer();
	if(CONTROL_COMPLEX) control = new ControlSystem;
	else control = new SimpleControlSystem;
	topm = new Relay(1,Relay::kBothDirections);
	botm = new Relay(2,Relay::kBothDirections);
	printf("Relays set.");
	joy = new Joystick(3);
}

void Robot2011::Disabled() {
	printf("TECH HIGH ROBOTICS 675 2011 CODE\n");
	printf("--------------------------------\n");
	drive->reset();
}

void Robot2011::Autonomous() {
	//arm->setAngle(angles[8]);
	/*drive->reset();
	t->Start();
	t->Reset();
	while(ds->IsAutonomous() && t->Get() < 15.0) {
		if(t->Get() > 11.0) { // if time is greater then 11 spit the tube
			topm->Set(Relay::kReverse);
			botm->Set(Relay::kForward);
			printf("releasing");
		}
		if(t->Get() > 2.0) {
			drive->autoupdate(t->Get());  //dont drive for 2 seconds while arn goes up
		}
		arm->autoupdate();
		printf(" %f",t->Get());
		printf("\n");
		//Wait(.05);
	}
	/*while(1) {
		drive->autoupdate(0);
		printf("\n");
	}*/
}

void Robot2011::OperatorControl() {
	while(ds->IsOperatorControl()) {
		drive->teleupdate(); 
		arm->update(control->GetClawTop(),control->GetClawBottom());
		if(joy->GetRawButton(1))
		{
			topm->Set(Relay::kReverse);
			botm->Set(Relay::kForward);
		}
		else if(joy->GetRawButton(3))
		{
			topm->Set(Relay::kForward);
			botm->Set(Relay::kReverse);
		}
		else if(joy->GetRawButton(4))
		{
			topm->Set(Relay::kForward);
			botm->Set(Relay::kForward);
		}
		else if(joy->GetRawButton(5))
		{
			topm->Set(Relay::kReverse);
			botm->Set(Relay::kReverse);
		}
		else
		{
			topm->Set(Relay::kOff);
			botm->Set(Relay::kOff);
		}
		minibot->update(control->GetMinibotDeploy(), control->GetMinibotShoot()/*,control->GetArmPosition()*/);
		Wait(0.0375);
		printf("\n");
	}
}
