#ifndef CONTROL_BASE
#define CONTROL_BASE

class ControlBase
{
public:
	virtual double GetArmPosition() = 0;
	virtual int GetClawTop() = 0;
	virtual int GetClawBottom() = 0;
	virtual bool GetMinibotDeploy() = 0;
	virtual bool GetMinibotShoot() = 0;
};

#endif
