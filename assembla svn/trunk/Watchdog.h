#ifndef Watchdog_h
#define Watchdog_h

class Watchdog //Ruff! Ruff!
{
protected:
    bool Enabled; //Watchdog Enabled
    bool Autonomous; //Disabled for Autonomous
    bool AutonomousDisable; //Disable During Autonomous
public:
    Watchdog() {Watchdog(1);} //assume disable for autonomous
    Watchdog(bool autodisable);
    ~Watchdog() {Enable();} //enable on deletion
    
    void Update();
    void Enable(); //on
    void Disable(); //off
};

#endif
