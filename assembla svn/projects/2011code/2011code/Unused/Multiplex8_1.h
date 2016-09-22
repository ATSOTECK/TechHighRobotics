/*#include "Includes.h"

class Multiplexer8_1 {
	DigitalOutput** s;
	DigitalInput* in;
	DriverStation *ds;
	bool inverted;
public:
	Multiplexer8_1(int firstSPort,int inPort) {
		inverted = false;
		s = new DigitalOutput*[3];
		in = new DigitalInput(inPort);
		for(int port = 0; port < 3;port++) {
			s[port] = new DigitalOutput(port+firstSPort);
			printf("port: %d",port+firstSPort);
		}
		ds = DriverStation::GetInstance();
	}
	void setInverted(bool inv) {
		inverted = inv;
	}
	bool getChannel(int ch) {
		s[0]->Set((ch/1) % 2); //black
		s[1]->Set((ch/2) % 2); //red
		s[2]->Set((ch/4) % 2); //white
		Wait(.005);
		ds->SetDigitalOut(ch+1,(bool)(inverted ? !in->Get() : in->Get()));
		return inverted ? !in->Get() : in->Get();
	}
};
*/