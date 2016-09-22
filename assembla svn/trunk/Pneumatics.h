#ifndef Pneumatics_h
#define Pneumatics_h

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

//Derive Each years pneumatics from this class
//Robot Specefic functions can be added to manipulate mechanisms
class PneumaticsSystem
{
protected:
    Compressor* c; //holds compressor
    PneumaticsMechanism* mech[6]; //holds mechanisms
    int findOpen(); //Finds the next open mech spot
public:
    void Init(); //initializes system
    void Init(int CompInputPort,int CompRelay)
    void Free(); //frees all mechanisms and compressor
    
    //Compressor Stuff
    void CompAdd(int CompInputPort,int CompRelay); //add compressor to system
    void CompEnable(); //enable compressor
    void CompDisable(); //disable compressor
    
    //Two Ways to add Mechanisms to system
    void AddMechanism(PneumaticsMechanism* Pointer);
    void AddMechanism(int OnPort,int OffPort,bool DefaultState);
    
    //Mechanism Setting
    void Set(int Id,bool On); //set one mech to state
    void SetAll(bool On); //set all mechs to state
    void Default(int Id); //set mech to default
    void DefaultAll(); //set all mechs to default
}

#endif
