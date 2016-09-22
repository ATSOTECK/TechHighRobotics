#include "Includes.h"
#include "Multiplex8_1.h"

#define NO_LINE_TIME 0.5
#define TURN_COEF .7

class LineSensor {
public:
	LineSensor(int port1,int nsensors);
	bool isLine();
	double getTurnValue(float dir);
protected:
	DriverStation *ds;
	double toPos(int sensor);
	int lastSensor; //last sensor that was on
	//Timer *t; //time since the line was last seen
	DigitalInput **sensors;
	int nsensors;
};
