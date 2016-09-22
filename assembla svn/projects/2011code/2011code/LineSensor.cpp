#include "LineSensor.h"
#include "ports.h"
#include "Includes.h"

LineSensor::LineSensor(int port1,int _nsensors) {
    nsensors = _nsensors;
    sensors = new DigitalInput*[nsensors];
    for(int port = 0; port < nsensors;port++) {
            sensors[port] = new DigitalInput(port+port1);
            printf("port: %d",port+port1);
    }
	ds = DriverStation::GetInstance();
}

/*
 * is the line sensed or under control?
 */
bool LineSensor::isLine() {
	for(int i = 0;i < nsensors;i++)
		if(!sensors[i]->Get())
			return true;
	return false;
}

/*
 * returns number from 0-1
 * if the number of sensors is not 1 or 0 than return dir
 */
double LineSensor::getTurnValue(float dir) {
	int onSensors = 0;
	float avg = 0;
	for(int i=0; i < nsensors; i++){
		lastSensor = i;
		if(!sensors[i]->Get()) {
			onSensors++;
			avg += i;
		}
		printf("%d",!sensors[i]->Get()); 
	}
	avg /= onSensors;
	float turnValue = (2 * avg/(nsensors-1) - 1) * TURN_COEF;
	
	if(onSensors > 2 || onSensors == 0) {
		turnValue = dir;
	}
	printf(" turn = %f ",turnValue);
	return turnValue;
}
