#include "Vision/Axiscamera.h"
#include "Vision/HSLImage.h"
#include "PIDController.h"
#include "Gyro.h"

#define MINIMUM_SCORE 0.01
//start
#include "WPILib.h"
#include "timer.h"
#include "math.h"
#include "Target.h"

//#define leftStick allSticks[0]
//#define rightStick allSticks[1]
//#define payloadStick allSticks[2]
/*
#define FORWARD_LIMET_1 5.0
#define FORWARD_LIMET_2 6.0
#define FORWARD_LIMET_3 7.0
#define AUTO_DELAY_1 10.0
#define AUTO_DELAY_2 9.0
#define AUTO_DELAY_3 8.0
#define SIDW_DIST 0.5
#define SIDWAYS_SPEED 0.8
#define FORWARD_SPEED 0.4
*/
#define FORWARD_SPEED 0.4
#define FORWARD_DIST 10.0
#define SIDWAYS_SPEED -0.8
#define SIDWAYS_DIST 1.0
#define AUTO_DELAY 0.0

#define CORRECTION .3 //correction for the line follow
#define CAM_CORRECTION .01
#define CAM_AIM_P 1.0
#define CAM_AIM_D 0.0

#define LINE_SENSORS 8
#define FRONT_SENSORS 4
#define BACK_SENSORS (LINE_SENSORS-FRONT_SENSORS)

#define KICKER_OFF 0//pnoomatix indexes
#define KICKER_ON 1
#define RAMP_FRONT_OFF 2
#define RAMP_FRONT_ON 3
#define RAMP_BACK_OFF 4
#define RAMP_BACK_ON 5
#define RAMP_RETRACT 6
#define RAMP_DEPLOY 7


#define BALL_DIST 3.0 //distance between balls in the grid
#define BUMP_TO_BALL 2 //distance the bot goes forward to get all the balls
//#define SIDE_DIST 2.0
#define DELAY_ZONE_2 4.0
#define DELAY_ZONE_3 8.0

double outputValue;

class SamplePIDOutput : public PIDOutput {
public:
	SamplePIDOutput() {
		rotation = 0;
	}

	void PIDWrite(float output) {
		rotation = output;
	}
	float rotation;
};

/*
 * 2010 Code for team 675.
 */
class DefaultRobot : public SimpleRobot {
	Joystick *rightStick, *leftStick, *payloadStick;
	DriverStation *ds; // driver station object
	DriverStationLCD *dsl; // not really an LCD
	Jaguar *lwfJ; //Jag for the left front motor
	Jaguar *lwbJ; //Jag for the left back motor
	Jaguar *rwfJ; //Jag for the right front motor
	Jaguar *rwbJ; //Jag for the right back motor
	Relay *roller; //ball controll motor
	DigitalInput *ballSensor; //beam sensor
	DigitalInput *compressor; //to see if the compressor is working
	Compressor *c; // compressor object
	Solenoid *s[8]; //pnoomatx Solinoids
	DigitalInput *line[LINE_SENSORS]; //line sensors format: left to right
	Timer *t,*t2; //timers
	Gyro *gyro; //Gyroscope input object
	AxisCamera *camera;
	SamplePIDOutput *pidOutput;
	bool isKicked;
	int drive; // 0,1,2
	bool lastSaveButtonState;
	bool driveReversed;
	double lastxPos; //of target
	bool wasTraking;
	
	double lwf, rwf, lwb, rwb; //Speeds for the wheels. Corospond to the Jags
	double throt;

    //Move function to control the bot during autonomous. 
    //Input ranges: -1 to 1
	void move(double yspeed,double xspeed,double rotation) { 
		lwfJ->Set(yspeed-xspeed+rotation);//TODO: put in the right -s
		rwfJ->Set(yspeed+xspeed-rotation);
		lwbJ->Set(yspeed+xspeed+rotation);
		rwbJ->Set(-(yspeed-xspeed-rotation));
		printf("%f,%f:::::%f,%f,%f,%f\n",xspeed,yspeed,lwfJ->Get(),rwfJ->Get(),lwbJ->Get(),rwbJ->Get());
	}
	
	void kick() {
		s[KICKER_ON]->Set(true);
		s[KICKER_OFF]->Set(false);
		printf("kicik");
		Wait(.5);
		s[KICKER_OFF]->Set(true);
		s[KICKER_ON]->Set(false);
		printf("unkick");
	}

public:
	/**
	 * Constructor for this robot subclass.
	 * Create an instance of a RobotDrive with left and right motors plugged into PWM
	 * ports 1 and 2 on the first digital module.
	 */ 
	DefaultRobot(void) {
		ds = DriverStation::GetInstance();
		dsl = DriverStationLCD::GetInstance();

		rightStick = new Joystick(1); // create the joysticks
		leftStick = new Joystick(2);
		payloadStick = new Joystick(3);

		lwfJ = new Jaguar(1);
		lwbJ = new Jaguar(2);
		rwfJ = new Jaguar(3);
		rwbJ = new Jaguar(4);
		roller = new Relay(2);
		
		//drive = new RobotDrive(1,2,3,4);
		ballSensor = new DigitalInput(2);
		//c = new Relay(1, Relay::kForwardOnly);
		c = new Compressor(1, 1);
		c->Start();
		compressor = new DigitalInput(1);
		for (int i=0; i<8; i++) {
			s[i] = new Solenoid(i+1);  //odd pistons are off so turn them on.
			s[i]->Set(!(i%2));            //even pistons are on so turn them off.
		}//kicker 0,3
		for (int i=0; i<LINE_SENSORS; i++)
			line[i] = new DigitalInput(i+3);
		throt=1;
		t = new Timer();//timers for forcing kicking rules
		t2 = new Timer();
		gyro = new Gyro(2);
		isKicked = false;
		drive = 0;
		lastSaveButtonState = false;
		//init camera
		
		camera = &AxisCamera::GetInstance();
		camera->WriteResolution(AxisCameraParams::kResolution_160x120);//Set resolution
		camera->WriteBrightness(0);//Set brightness
		camera->WriteMaxFPS(5);
		printf("camera initialized");
		//Update the motors at least every 100ms.
		GetWatchdog().SetExpiration(0.1);
	}

	void Disabled(void) {
		printf("I'm Disabled!!!!!!!!!!!!! and I'm reseting pnoomatx");
		for (int j=0; j<8; j++) {  //odd pistons are off so turn them on.
			s[j]->Set(!(j%2));            //even pistons are on so turn them off.
			printf("Resetting: %d\n", j);
		}
		move(0,0,0);
		printf("stopped\n");
		t->Stop();
		t2->Stop();
		while(IsDisabled()) {
			if(payloadStick->GetRawButton(8))
				printf("payload Stick\n");
			if(rightStick->GetRawButton(8))
				printf("right Stick\n");
			if(payloadStick->GetRawButton(8))
				printf("left Stick\n");
		}
	}
	/**
	 * kicks balls
	 */
	void Autonomous(void) {
		printf("AUTO CONTROL BEGIN HI aginnnn\n");
		GetWatchdog().SetEnabled(false);
		Wait(AUTO_DELAY);
		t->Start();
		t->Reset();
		move(FORWARD_SPEED,0,0);
		while(t->Get() < FORWARD_DIST) {
			if(!ballSensor->Get()) {
				move(0,0,0);
				//roller->Set(Relay::kReverse);
				//Wait(0.5);
				//roller->Set(Relay::kForward);
				//Wait(0.5);
				kick();
				Wait(2.0);
				move(FORWARD_SPEED,0,0);
				if(ds->GetLocation() == 1) {
					break;
				}
			}
		}
		move(0,SIDWAYS_SPEED,0);
		Wait(SIDWAYS_DIST);
		move(0,0,0);
		GetWatchdog().SetEnabled(true);
	}

	
	/*
	 * 
	 */
	void OperatorControl(void) {
		t->Start(); //Start timers for kicker
		t2->Start();
		/*
		pidOutput = new SamplePIDOutput();
		PIDController turnController( 0.1, // P
				0.00, // I
				0.5, // D
				gyro, // source
				pidOutput, // output
				0.005); // period
		turnController.SetInputRange(-360.0, 360.0);
		turnController.SetOutputRange(-0.6, 0.6);
		turnController.SetTolerance(1.0 / 90.0 * 100);
		turnController.Disable();
		gyro->SetSensitivity(0.007);
		bool lastTrigger = false;
		*/
		while (IsOperatorControl()) {
			GetWatchdog().Feed();
			
			if((t2->Get() > 0.7) && isKicked ) {
				isKicked = false;
				printf("Unkick %f\n", t2->Get());
				t->Reset();
			}
			if((t->Get() > 2.1) && (!isKicked) 
					&& (!ballSensor->Get() || payloadStick->GetTrigger()) && rightStick->GetTrigger()) {
				isKicked = true;
				printf("Kick\n");
				t2->Reset();
			}
			s[KICKER_ON]->Set((isKicked && t2->Get() > 0.5));
			s[KICKER_OFF]->Set(!(isKicked && t2->Get() > 0.5));
			//printf("%d %d %f %f %d\n",payloadStick->GetTrigger(),isKicked,t->Get(),t2->Get(), ballSensor->Get());
			
			if(rightStick->GetRawButton(3)) {
				roller->Set(Relay::kReverse);
			} else if (rightStick->GetRawButton(2)) {
				roller->Set(Relay::kForward);
			} else {
				roller->Set(Relay::kOff);
			}
			
			if(isKicked) {
				roller->Set(Relay::kForward);
			}
			
			if (payloadStick->GetRawButton(4)){ //lift Front of ramp
				s[RAMP_FRONT_ON]->Set(true);
				s[RAMP_FRONT_OFF]->Set(false);
				printf("lift front\n");
			}
			if (payloadStick->GetRawButton(5)){ //lift back of ramp
				s[RAMP_BACK_ON]->Set(true);
				s[RAMP_BACK_OFF]->Set(false);
				printf("lift back\n");
			}
			if (payloadStick->GetRawButton(2)) {//reset solenoids
				for (int j=0; j<8; j++) {  //odd pistons are off so turn them on.
					s[j]->Set(!(j%2));            //even pistons are on so turn them off.
					printf("Resetting: %d\n", j);
				}
			}
			if (payloadStick->GetRawButton(3)) { //deploy ramp
				s[RAMP_DEPLOY]->Set(true);
				s[RAMP_RETRACT]->Set(false);
				
				printf("deploy\n");
			} else {
				s[RAMP_DEPLOY]->Set(false);
				s[RAMP_RETRACT]->Set(true);
				//printf("retract\n");
			}
			bool driveNormal = true;
			/*if (rightStick->GetRawButton(2)) {
				if (rightStick->GetRawButton(2) != lastTrigger) // check if trigger changed TODO: cam aim
					turnController.Enable();
				//if there's a fresh and we're at the previous target heading then
				// get a camera image and process it
				if (camera->IsFreshImage() && turnController.OnTarget() ) {
					// get the gyro heading that goes with this image
					double gyroAngle = gyro->PIDGet();
					
					// get the camera image
					ColorImage *image = camera->GetImage();

					// find FRC targets in the image
					vector<Target> targets = Target::FindCircularTargets(image);
					delete image;
					if (targets.size() == 0 || targets[0].m_score < MINIMUM_SCORE)
					{
						// no targets found. Make sure the first one in the list is 0,0
						// since the dashboard program annotates the first target in green
						// and the others in magenta. With no qualified targets, they'll all
						// be magenta.
						Target nullTarget;
						nullTarget.m_majorRadius = 0.0;
						nullTarget.m_minorRadius = 0.0;
						nullTarget.m_score = 0.0;
						if (targets.size() == 0)
							targets.push_back(nullTarget);
						else
							targets.insert(targets.begin(), nullTarget);

						if (targets.size() == 0)
							printf("No target found\n\n");
						else
							printf("No valid targets found, best score: %f\n", targets[0].m_score);
					}
					else {
						// We have some targets.
						// set the new PID heading setpoint to the first target in the list
						double horizontalAngle = targets[0].GetHorizontalAngle();
						double setPoint = gyroAngle + horizontalAngle;

						turnController.SetSetpoint(setPoint);
						
						// send dashbaord data for target tracking
//						targets[0].Print();
					}
				}
            	driveNormal = false;
            	lwfJ->Set(pidOutput->rotation);
    			rwfJ->Set(-pidOutput->rotation);
    			lwbJ->Set(pidOutput->rotation);
    			rwbJ->Set(-pidOutput->rotation);
			}
			else if(lastTrigger){
				turnController.Disable();
			}*/
			
			if (leftStick->GetTrigger()) {//line follow TODO: line follower Test
                lwf = rwf = lwb = rwb = -leftStick->GetY(); //start going forward
				int detected=0,place = 0; //amount of sensors sensing the line, and place the line is [-SENSORS+1,SENSORS-1]
                for(int i = 0;i < FRONT_SENSORS;i++) { //loop through the sensors
                    if(line[i]->Get()) { //if line sensor i senses the line
                        detected++; // record that sensor was detected
                        place += 2*i+1-FRONT_SENSORS; // convert i to a place
                    }
                }
                place /= detected; //turn place into an average
                if(rwf > 0) { //if going forward
	                rwf += place*CORRECTION;
	                lwf -= place*CORRECTION;
                } else { //if going backward
                	rwb -= place*CORRECTION;
                	lwb += place*CORRECTION;
                }
                lwfJ->Set(lwf);
				lwbJ->Set(lwb);
				rwfJ->Set(rwf);
				rwbJ->Set(-rwb);
                if(detected > 0)
                	driveNormal = false;
                
                printf("%d|",ballSensor->Get());
            	for(int x = 0;x < 4;x++)
					printf("%d",line[x]->Get());
				printf("|");
                printf("detected: %d place: %d  #%s# MOTORS: %f,%f,%f,%f\n",
                		detected,place,(detected > 0 && detected < 3) ? "f" : "df",
                				lwf,rwf,lwb,rwb);
			}
			if(driveNormal) {
				if(drive == 0) {
					throt = 1;
					lwf = (-rightStick->GetY()*throt)+(leftStick->GetX()*throt)
							-(-rightStick->GetX()*throt);
					rwf = (-rightStick->GetY()*throt)-(leftStick->GetX()*throt)
							+(-rightStick->GetX()*throt);
					lwb = (-rightStick->GetY()*throt)-(leftStick->GetX()*throt)
							-(-rightStick->GetX()*throt);
					rwb = (-rightStick->GetY()*throt)+(leftStick->GetX()*throt)
							+(-rightStick->GetX()*throt);
					//printf("luke drive\n");
				} else if(drive == 1) {//Huntar drivee
					lwf = -leftStick->GetY()+leftStick->GetX();
					rwf = -rightStick->GetY()-rightStick->GetX();
					lwb = -leftStick->GetY()-leftStick->GetX();
					rwb = -rightStick->GetY()+rightStick->GetX();
					//printf("huntar drive\n");
				} else if(drive == 2) {//Huntar drive 2
					lwf = -leftStick->GetY()+rightStick->GetX();
					rwf = -leftStick->GetY()-rightStick->GetX();
					lwb = -rightStick->GetY()-rightStick->GetX();
					rwb = -rightStick->GetY()+rightStick->GetX();
					//printf("huntar drive2\n");
				} else if(drive == 3) {
					lwf = rightStick->GetY();
					rwf = rightStick->GetX();
					lwb = leftStick->GetY();
					rwb = leftStick->GetX();
					printf("wheel testing:%f,%f,%f,%f\n",lwf, rwf, lwb, rwb);
				}
				if(!driveReversed) {
					lwfJ->Set(lwf);
					lwbJ->Set(lwb);//TODO: put in the right -s
					rwfJ->Set(rwf);
					rwbJ->Set(-rwb);//-
				} else if(driveNormal){
					lwfJ->Set(-rwb);
					lwbJ->Set(-rwf);
					rwfJ->Set(-lwb);
					rwbJ->Set(lwf);//-
				}
			}

			if(payloadStick->GetRawButton(6))
				drive = 0;
			if(payloadStick->GetRawButton(7))
				drive = 1;
			if(payloadStick->GetRawButton(10))
				drive = 2;
			if(payloadStick->GetRawButton(11))
				drive = 3;

			if(payloadStick->GetRawButton(8))
				printf("payload Stick\n");
			if(rightStick->GetRawButton(8))
				printf("right Stick\n");
			if(payloadStick->GetRawButton(8))
				printf("left Stick\n");
			if(ballSensor->Get())
				dsl->Printf(dsl->kUser_Line1, 1, "ball!");
			if(leftStick->GetRawButton(3))
				driveReversed = false;
			else if(leftStick->GetRawButton(2))
				driveReversed = true;//Dont do that, james
			lastSaveButtonState = rightStick->GetRawButton(9);
		}
	}
};
START_ROBOT_CLASS(DefaultRobot);
