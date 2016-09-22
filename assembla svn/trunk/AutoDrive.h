#ifndef _AUTODRIVE_H
#define	_AUTODRIVE_H

#define TURN_P 1.0
#define TURN_I 0.0 
#define TURN_D 0.5
#defint TURN_TOLERENCE_DEG 5
#define DRIVE_P 0.5
#define DRIVE_I 0.0
#define DRIVE_D 0.0
#define DRIVE_TOLERANCE_FT .5

class AutoDrive : public Drivetrain {
private:
    float driveSpeed;
    float turnSpeed;
    Gyro *gyro;
    Encoder *encoder;
    PIDController *turnController
    PIDController *distanceController
public:
    AutoDrive();
    void moveDistance(float distance);
    void turnAngle(float angle);
    void update();
    void stop();
};

#endif
