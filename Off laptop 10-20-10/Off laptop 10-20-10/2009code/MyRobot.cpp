#include <WPILib.h>
#include <math.h>
#include <Victor.h>

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 

/* Constants */

#define IDLER_WHEEL_CIRC 		8.82788
#define DRIVE_WHEEL_CIRC 		19.0381
#define IDLER_TICKS 			24
#define DRIVE_TICKS				7000
#define IDLER_TICKS_PER_INCH	IDLER_TICKS / IDLER_WHEEL_CIRC
#define DRIVE_TICKS_PER_INCH    DRIVE_TICKS / DRIVE_WHEEL_CIRC
#define IDLER_INCHES_PER_TICK   (IDLER_WHEEL_CIRC / IDLER_TICKS)*1.055*0.967969
#define DRIVE_INCHES_PER_TICK   (DRIVE_WHEEL_CIRC / DRIVE_TICKS)

#define MAX_SPEED 50

#define PROPORTIONAL 0.8
#define INTEGRAL 0.2
#define DERIVATIVE 0.3

Timer ellapsedTime;
int direction = 0;

inline float abs(float val)
{
	return val>0 ? val : val*-1;
}

int sign(float f)
{
	if(f>0)
	{
		return 1;
	}
	
	if(f<0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

class PID
{
public:
	PID(float _p, float _i, float _d)
	{
		p = _p;
		i = _i;
		d = _d;
		integral = 0;
		old_err = 0;
		i = 0;
		for(int j = 0;i<16;i++)
		{
			intArray[j] = 0;
		}
	}
	float calc(float set, float actual)
	{	
		float retVal = 0;
		float err = set - actual;
		
		retVal = p * 1.5 * err;// + i * integrate(err) * d *(err - old_err);		
		
		old_actual = actual;
		old_err = err;
		
		return retVal;
	}
	float calc(float set, float actual, float temp_p, float temp_i, float temp_d)
	{	
		float retVal = 0;
		float err = set - actual;
		
		retVal = temp_p * 1.5 * err; // + temp_i * integrate(err) * temp_d *(err - old_err);		
		
		old_actual = actual;
		old_err = err;
		
		return retVal;
	}
	void reset(void)
	{
		integral = 0;
		old_err = 0;
		old_actual = 0;
	}
	float getIntegral(void)
	{
		return integral;
	}
	
private:
	float p, i, d, old_err, old_actual, integral;
	float intArray[16];
	int j;
	
	float integrate(float integrand)
	{
		intArray[j] = integrand;
		j++;
		if(j==16)
			j=0;
		
		for(int k = 0;k<16;k++)
		{
			integral += intArray[k];
		}
		integral /= 16;
		return integral;
	}
};

class RobotDemo : public SimpleRobot
{
	RobotDrive *myRobot; // robot drive system
	Joystick *stick; // only joystick
	Joystick *rightStick; //other joystick
	Joystick *payload; //other joystick
	Joystick *fourthStick;
	Victor  *vic1;
	Victor  *vic2;
	Relay   *agitator;
	
	
	//Servo servo;
	//RobotDrive *myRobot;
	//Range greenHue, greenSat, greenLum;

public:
	RobotDemo(void)
		//myRobot(1, 2),	// these must be initialized in the same order
		//stick(1),		// as they are declared above.
		//servo(3)
	{
		GetWatchdog().SetExpiration(100);
		vic1  = new Victor(3);
		vic2  = new Victor(4);
		myRobot = new RobotDrive(1, 2);
		stick = new Joystick(1);
		rightStick = new Joystick(3);//new Joystick(2);
		payload = new Joystick(3);
		fourthStick = new Joystick(4);
		agitator = new Relay(1);
		
		ellapsedTime.Start();
		/*DriverStationLCD *dsLCD = DriverStationLCD::GetInstance();
					dsLCD->Printf(DriverStationLCD::kMain_Line6, 6, "Hello World");
					dsLCD->Printf(DriverStationLCD::kUser_Line2, 8, ":%7.1f", GetClock());
					dsLCD->Printf(DriverStationLCD::kUser_Line3, 17, "%7.1f", GetClock());
					dsLCD->Printf(DriverStationLCD::kUser_Line4, 7, "%7.1f", GetClock());
					dsLCD->Printf(DriverStationLCD::kUser_Line5, 4, "%7.1f", GetClock());
					dsLCD->Printf(DriverStationLCD::kUser_Line6, 10, "%7.1f", GetClock());
					printf("%-7.1f", GetClock());
					dsLCD->UpdateLCD();*/
		// values for tracking a target - may need tweaking in your environment 

		
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
		PID rPID(0.244, 0.2, 0);
		PID lPID(0.244, 0.2, 0);
		
		Timer time;
		
		time.Start();
		
		
		Encoder leftIdler(3,4);
		leftIdler.Start();
		Encoder rightIdler(1,2);
		rightIdler.Start();
		
		Encoder rightDrive(5,6);
		rightDrive.Start();
		Encoder leftDrive(7,8);
		leftDrive.Start();
				
		GetWatchdog().SetEnabled(false);
		myRobot->Drive(0.0, 0.0); 	// stop robot
		
			
	
			while(IsAutonomous())
			{
				if(time.Get()<6)
					myRobot->TankDrive(-.68,-1);
				else
					myRobot->TankDrive(1,.9);
			} 
				myRobot->Drive(0.0, 0.0);
		
		
	}

	
	void OperatorControl(void)
	{
		GetWatchdog().SetEnabled(true);
		
		float rightOut = 0;
		float leftOut = 0;
		float rightDriveSpeed = 0;
		float rightIdlerSpeed = 0;
		float leftIdlerSpeed = 0;
		float leftDriveSpeed = 0;
		float rightSet = 0;
		float leftSet = 0;

		
		Timer time;
		
		PID rPID(1, .5, .3);
		PID lPID(1, .5, .3);
		
		time.Start();
		
		
		Encoder leftIdler(3,4);
		leftIdler.Start();
		Encoder rightIdler(1,2);
		rightIdler.Start();
		
		Encoder rightDrive(5,6);
		rightDrive.Start();
		Encoder leftDrive(7,8);
		leftDrive.Start();
		
		while (IsOperatorControl())
		{
			
			GetWatchdog().Feed();
			
			if (rightStick->GetTrigger() || payload->GetTrigger())
			{
				vic2->Set(0.929134);
				vic1->Set(0.795276);
			}
			else if(rightStick->GetTop() || payload->GetTop())
			{
				vic1->Set(1);
				vic2->Set(-1);
			}
			else if(payload->GetRawButton(3))
			{
				vic1->Set(1);
				vic2->Set(1);
			}
			else if(payload->GetRawButton(6))
			{
				vic2->Set(0);
				vic1->Set(-1);
			}
			else
			{
				vic1->Set(0);
				vic2->Set(0);
			}
			
			
		
			
			if(payload->GetY()>0)
			{
				printf("turbulizing    ", rightSet);
				agitator->Set(Relay::kForward);
			}
			else if(payload->GetY()<0)
			{
				printf("turbulizing    ", rightSet);
				agitator->Set(Relay::kReverse);
			}
			else
			{
				printf("not turbulizing", rightSet);
				agitator->Set(Relay::kOff);
			}
			
			
			
			if(time.Get() > 0.05)
			{
								
				rightIdlerSpeed = (-1 * rightIdler.Get() * IDLER_INCHES_PER_TICK)/5;
				rightDriveSpeed = (rightDrive.Get() * DRIVE_INCHES_PER_TICK)/5;
				leftIdlerSpeed =  (-1 * leftIdler.Get() * IDLER_INCHES_PER_TICK)/5;
				leftDriveSpeed = (leftDrive.Get() * DRIVE_INCHES_PER_TICK)/5;
				
				if(abs(rightStick->GetY() - rightIdlerSpeed)>0.2)
				{
					
					rightSet = 0.35 * sign(rightStick->GetY()-rightIdlerSpeed) + rightIdlerSpeed;
				}
				else
				{
					rightSet = rightStick->GetY();
				}
					
				if(abs(stick->GetY() - leftIdlerSpeed)>0.2)
				{
					leftSet  = 0.35 * sign(stick->GetY()-leftIdlerSpeed) + leftIdlerSpeed;
				}
				else
				{
					leftSet = stick->GetY();
				}
				
				if(stick->GetTrigger())
					
				{
					rightOut += rPID.calc(rightStick->GetY(), rightDriveSpeed, 0.244, 0.2, 0);
					leftOut -= lPID.calc(-stick->GetY(), leftDriveSpeed, 0.244, 0.2, 0);
				}
				else
				{
					rightOut += rPID.calc(rightSet, rightDriveSpeed, 0.244, 0.2, 0);
					leftOut -= lPID.calc(-leftSet, leftDriveSpeed, 0.244, 0.2, 0);
				}
				
				//myRobot->TankDrive(leftOut, rightOut);
				myRobot->ArcadeDrive(rightStick);
				
				printf("%f", (rightStick->GetThrottle()/4)+0.25);
				time.Reset();
				rightDrive.Reset();
				rightIdler.Reset();
				leftDrive.Reset();
				leftIdler.Reset();
				
				printf("%f", payload->GetThrottle());
				printf("tcs %f ", ((rightStick->GetThrottle()/4)+0.25));
				printf("%f ", fourthStick->GetThrottle());
				printf("%f ", rightStick->GetY());
			}
			
		}
	}
	
};



START_ROBOT_CLASS(RobotDemo);

