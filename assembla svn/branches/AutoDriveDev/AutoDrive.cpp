#include "AutoDrive.h"

class PointerPIDOutput : public PIDOutput {
    float *pOut;
public:
    RobotRotator(float *_pOut) {
        pOut = _pOut;
    }
    void PIDWrite(float output) {
        *pOut = output;
    }
}

class PIDEncoder : public PIDSource{
    Encoder *e;
public:
    PIDEncoder(Encoder *_e) {
        e = _e;
    }
    double PIDGet() {
        return e->get();
    }
}

AutoDrive::AutoDrive(Gyro *_gyro,Encoder *_encoder) {
    gyro = _gyro;
    encoder = _encoder; //save refrences to the gyro and encoder
    PIDSource *dist = new PIDEncoder(encoder);
    PIDOutput *robotRotator = new PointerPIDOutput(&turnSpeed);
    PIDOutput *robotMover = new PointerPIDOutput(&driveSpeed); //probably should delete these somewhere but I don't want to
    
    turnController = new PIDController(TURN_P,TURN_I,TURN_D,gyro,robotRotator);
    turnController->SetInputRange(-360.0, 360.0);
	turnController->SetTolerance(TURN_TOLERANCE_DEG / 360.0 * 100);
	turnController->Disable();
	
    distController = new PIDController(MOVE_P,MOVE_I,MOVE_D,dist,robotMover);
    turnController->SetInputRange(-10.0, 10.0); //ten feet
	turnController->SetTolerance(DRIVE_TOLERANCE_FT);
	turnController->Disable();
}

void AutoDrive::setDistance(float distance) { //set the distance you want the
    distController->SetSetpoint(distance + encoder.Get()) //distance is reletive to where you are now
}

void AutoDrive::setAngle(float angle) {
    distController->SetSetpoint(angle + gyro.Get()) //distance is reletive to where you are now
}

void Autodrive::stop() {
    turnController->Disable();
    distController->Disable();
    ArcadeDrive(0,0);
}

void Autodrive::update() {
    ArcadeDrive(*driveSpeed,*turnSpeed);
}
