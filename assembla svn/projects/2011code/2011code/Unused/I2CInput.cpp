/*#include "I2CInput.h"

#define CHIP_ADDRESS 0x70

I2CInput::I2CInput(){
	DigitalModule* dm = DigitalModule::GetInstance(4);
	i2c = dm->GetI2C(CHIP_ADDRESS);
	data = new UINT8;
	*data = 0;
	refresh = 0;
	i2c->Write(0xFF,0);
}

void I2CInput::update()
{
	i2c->Write(0,0);
	if(refresh++ >= 2)
	{
		i2c->Write(0xFF,0);
		refresh = 0;
	}
	//i2c->Read(0,data);
}

bool I2CInput::getBit(int bit)
{
	if(*data & (1 << bit) == (1 << bit)) return true;
	else return false;
}*/
