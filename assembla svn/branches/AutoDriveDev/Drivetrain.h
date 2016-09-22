#ifndef _DRIVETRAIN_H
#define	_DRIVETRAIN_H

class Drivetrain : public RobotDrive {
public:
    Drivetrain(int frontRight,int );

    Drivetrain(UINT32 leftMotorChannel, UINT32 rightMotorChannel, float sensitivity = 0.5);
	RobotDrive(UINT32 frontLeftMotorChannel, UINT32 rearLeftMotorChannel,
				UINT32 frontRightMotorChannel, UINT32 rearRightMotorChannel, float sensitivity = 0.5);
	RobotDrive(SpeedController *leftMotor, SpeedController *rightMotor, float sensitivity = 0.5);
	RobotDrive(SpeedController &leftMotor, SpeedController &rightMotor, float sensitivity = 0.5);
	RobotDrive(SpeedController *frontLeftMotor, SpeedController *rearLeftMotor,
				SpeedController *frontRightMotor, SpeedController *rearRightMotor,
				float sensitivity = 0.5);
	RobotDrive(SpeedController &frontLeftMotor, SpeedController &rearLeftMotor,
				SpeedController &frontRightMotor, SpeedController &rearRightMotor,
				float sensitivity = 0.5);

    virtual ~Drivetrain();
private:

};

#endif

