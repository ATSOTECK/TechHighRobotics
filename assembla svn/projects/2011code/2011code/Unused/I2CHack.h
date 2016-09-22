/*#ifndef I2C_HACK_H
#define I2C_HACK_H

#include "Includes.h"

class I2CHack : public I2C
{
public:
	I2CHack(DigitalModule *module, UINT8 deviceAddress) : I2C(module,deviceAddress) {};
	bool Read(UINT8 count,UINT8* buffer);
	bool Write(UINT8* data);
};

#endif
*/