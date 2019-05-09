#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define STEP_I2C_ADDR 	 	0x20

#define IN_PORT0 		0x00
#define IN_PORT1		0x01
#define OUT_PORT0		0x02
#define OUT_PORT1		0x03
#define POLARITY_IVE_PORT0	0x04
#define POLARITY_IVE_PORT1	0x05
#define CONFIG_PORT0		0x06
#define CONFIG_PORT1		0x07

const int aPinSwitch[2] = {6,5};

const int aPhase_2[4] = {0xC0, 0x60, 0x30, 0x90};

const int aPhase_12[8] = {0x10, 0x30, 0x20, 0x60, 0x40, 0xC0, 0x80, 0x90};

int fd;

int interruptFlag = 0;

void changePhaseTo2(void)
{
	interruptFlag = 0;
}

void changePhaseTo12(void)
{
	interruptFlag = 1;
}

int main(void)
{
	if((fd = wiringPiI2CSetup(STEP_I2C_ADDR))<0)
	{
		return -1;
	}

	wiringPiSetupGpio();

	int i;
	for(i=0; i<2; i++)
	{
		pinMode(aPinSwitch[i], INPUT);
	}

	wiringPiI2CWriteReg16(fd, CONFIG_PORT0, 0x00);

	wiringPiISR(aPinSwitch[0], INT_EDGE_RISING, changePhaseTo2);
	wiringPiISR(aPinSwitch[1], INT_EDGE_RISING, changePhaseTo12);
	

	while(1)
	{
		if(interruptFlag ==0)
		{
			for(i=0; i<4; i++)
			{
				wiringPiI2CWriteReg16(fd, OUT_PORT0, aPhase_2[i]);
				delay(10);
			}
		}
		else
		{


			for(i=7; i>=0; i--)
			{
				wiringPiI2CWriteReg16(fd, OUT_PORT0, aPhase_12[i]);
				delay(10);
			}
		}
	}
	return 0;
}
