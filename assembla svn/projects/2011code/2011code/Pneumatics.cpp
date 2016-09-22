#include "Pneumatics.h"

//Pneumatics Mechanism
PneumaticsMechanism::PneumaticsMechanism(int OnPort,int OffPort)
{
    PneumaticsMechanism(OnPort,OffPort,false);
}

PneumaticsMechanism::PneumaticsMechanism(int OnPort,int OffPort,bool DefaultState)
{
    onSolenoid = new Solenoid(OnPort);
    offSolenoid = new Solenoid(OffPort);
    defaultState = DefaultState;
    Default();
}

PneumaticsMechanism::~PneumaticsMechanism()
{
    if(onSolenoid != NULL) delete onSolenoid;
    if(offSolenoid != NULL) delete offSolenoid;
}

bool PneumaticsMechanism::IsOn()
{
    return on;
}

void PneumaticsMechanism::On()
{
    onSolenoid->Set(true);
    offSolenoid->Set(false);
    printf("On()");
    on = true;
}

void PneumaticsMechanism::Off()
{
    onSolenoid->Set(false);
    offSolenoid->Set(true);
    on = false;
}

void PneumaticsMechanism::Default()
{
    if(defaultState) On();
    else Off();
}
