class PneumaticMechanism {
private:
    Solenoid *onSol;
    Solonoid *offSol;
public:
    PnumaticPiston(int onPort,int offPort);
    void on();
    void off();
}

class Pneumatics2010 {
private:
    Compressor *c;
    PneumaticMechanism *kikker;
    PneumaticMechanism *rampFront;
    PneumaticMechanism *rampBack;
    PneumaticMechanism *rampDeploy;
    Timer *kicktimer; //for timing kikking
public:
    Pneumatics2010();//ints compresser, sets solonoids to 
    teleopUpdate();//does stuff according to buttons
    kick(); //kick function for atonomus
    setEnabled(bool enabled);//deafault=true, if false, stops the compressor and stops pnumatics from changing state
}
