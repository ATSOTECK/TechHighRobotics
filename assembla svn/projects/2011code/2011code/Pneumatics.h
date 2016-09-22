#ifndef Pneumatics_h
#define Pneumatics_h

#include "Includes.h"

class PneumaticsMechanism
{
protected:
    bool on;
    bool defaultState;
    Solenoid* onSolenoid;
    Solenoid* offSolenoid;
public:
    PneumaticsMechanism(int OnPort,int OffPort);
    PneumaticsMechanism(int OnPort,int OffPort,bool DefaultState);
    ~PneumaticsMechanism();
    
    bool IsOn();
    void On();
    void Off();
    void Default();
};

#endif
