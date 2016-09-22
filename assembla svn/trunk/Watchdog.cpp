#include "Watchdog.h"

Watchdog::Watchdog(bool autodisable)
{
    Enabled = true;
    Autonomous = false;
    AutonomousDisable = autodisable;
    GetWatchdog().SetExpiration(0.1); //Expiration = 100 ms
}

void Watchdog::Update()
{
    if(AutonomousDisable)
    {
        if(IsAutonomous() && !Autonomous) //disable if autonomous and hasn't already been disabled for autonomous
        {
            Autonomous = true;
            Disable();
        }
        
        if(!IsAutonomous() && Autonomous) //Enable if not autonomous AND was disabled for autonomous
        {
            Autonomous = false;
            Enable();
        }
    }
    
    if(Enabled) GetWatchdog().Feed(); //feed if enabled
}

void Watchdog::Enable() //on
{
    Enabled = true;
    GetWatchdog().SetEnabled(true);
}

void Watchdog::Disable() //off
{
    Enabled = false;
    GetWatchdog().SetEnabled(false);
}
