#ifndef LogitechController_h
#define LogitechController_h

class LogitechController
{
protected:
    Joystick* Controller;
public:
    LogitechController() {LogitechController(1);} //assume port 1
    LogitechController(int port);
    ~LogitechController();
    
    double GetX1(); //Axis 1
    double GetY1();
    double GetX2(); //Axis 2
    double GetY2();
    bool GetButton(int index);
};

#endif
