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

//Pneumatics System
int PneumaticsSystem::findOpen()
{
    int temp = 0;
    while(mech[temp] != 0)
    {
        mech++;
        if(mech > 5) return -1;
    }
    return temp;
}

void PneumaticsSystem::Init()
{
    //set all pointers to 0
    c = 0;
    for(int a = 0;a < 6;a++) mech[a] = 0;
}

void PneumaticsSystem::Init(int CompInputPort,int CompRelay)
{
    Init();
    CompAdd(CompInputPort,CompRelay);
}

void PneumaticsSystem::Free()
{
    //free all filled pointers
    if(c != 0) delete c;
    for(int a = 0;a < 6;a++)
    {
        if(mech[a] != 0) delete mech[a];
    }
}

void PneumaticsSystem::CompAdd(int CompInputPort,int CompRelay)
{
    c = new Compressor(CompInputPort,CompRelay);
}

void PneumaticsSystem::CompEnable()
{
    c->Start();
}

void PneumaticsSystem::CompDisable()
{
    c->Stop();
}

void PneumaticsSystem::AddMechanism(PneumaticsMechanism* Pointer)
{
    mech[findOpen()] = Pointer;
}

void PneumaticsSystem::AddMechanism(int OnPort,int OffPort,bool DefaultState)
{
    mech[findOpen()] = new PneumaticsMechanism(OnPort,OffPort,DefaultState);
}

void PneumaticsSystem::Set(int Id,bool On)
{
    if(mech[Id] != 0)
    {
        if(on) mech[Id]->On();
        else mech[Id]->Off();
    }
}

void PneumaticsSystem::SetAll(bool On)
{
    for(int a = 0;a < 6;a++)
    {
        if(mech[Id] != 0)
        {
            if(on) mech[a]->On();
            else mech[a]->Off();
        }
    }
}

void PneumaticsSystem::Default(int Id)
{
    if(mech[Id] != 0)
    {
        mech[Id]->Default();
    }
}

void PneumaticsSystem::DefaultAll()
{
    for(int a = 0;a < 6;a++)
    {
        if(mech[Id] != 0)
        {
            mech[a]->Default();
        }
    }
}
