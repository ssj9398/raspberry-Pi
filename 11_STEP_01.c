#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define STEP_I2C_ADDR    0x20

#define IN_PORT0 	 0x00
#define IN_PORT1	 0x01
#define OUT_PORT0	 0x02
#define OUT_PORT1	 0x03
#define POLARITY_IVE_PORT0  0x04
#define POLARITY_IVE_PORT1  0x05
#define CONFIG_PORT0 	    0X06
#define CONFIG_PORT1	    0x07

const int aPhase_1[4] = {0x80, 0x40, 0x20, 0x10};

int fd;

int main(void)
{
	if((fd=wiringPiI2CSetup(STEP_I2C_ADDR))<0)
	{
		return -1;
	}

	wiringPiI2CWriteReg16(fd, CONFIG_PORT0, 0x00);

	int i;

	while(1)
	{
	for(i=0; i<4; i++)
	{
		wiringPiI2CWriteReg16(fd, OUT_PORT0, aPhase_1[i]);
		delay(10);
	}
	}
	return 0;
}
