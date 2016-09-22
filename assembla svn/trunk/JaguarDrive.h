#ifndef JaguarDrive_h
#define JaguarDrive_h

class JaguarDrive //Rarrrr...
{
protected:
    bool VariablesEnabled; //Enable Sync with Doubles
    Jaguar* Jaguar[8]; //Jaguar Pointers
    double* Variable[8]; //Doubles to sync with
    bool Reversed[8]; //Motor is reversed
    bool RightSide[8]; //Motor is on right side (for Movement Functions)
public:
    JaguarDrive() {JaguarDrive(false);} //Assume No Sync
    JaguarDrive(bool enablevariables);
    ~JaguarDrive();
    
    void SetJaguar(int id,Jaguar* pointer)      {Jaguar[id] = pointer;} //Set Jaguar Pointer
    void SetVariable(int id,double* pointer)    {Variable[id] = pointer;} //Set Variable Pointer
    void SetReverse(); //Reverse all
    void SetReverse(int id); //reverse one
    void SetSide(int id,bool isonright)         {RightSide[id] = isonright;} //Set Side
    
    void Update();
    void Move(double speed,double turn); //speed (-1 (Backwards) to 1 (Forwards)) and turn (-1 (Left) to 1 (Right))
    void SetRightSide(double speed); //Set Right Side (Tank Drive)
    void SetLeftSide(double speed); //Set Left Side (Tank Drive)
};

#endif
