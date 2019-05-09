#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define FND_I2C_ADDR               0x21

#define IN_PORT0 		   0x00
#define IN_PORT1                   0x01
#define OUT_PORT0                  0x02
#define OUT_PORT1                  0x03
#define POLARITY_IVE_PORT0	   0x04
#define POLARITY_IVE_PORT1 	   0x05
#define CONFIG_PORT0		   0x06
#define CONFIG_PORT1		   0x07

const int aFndData[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0x3E, 0xE0, 0xFE, 0xF6};

const int fndSelect = 0xFB;

int fd;

int main(void)
{
	if((fd=wiringPiI2CSetup(FND_I2C_ADDR))<0)
	{
		return -1;
	}
	wiringPiI2CWriteReg16(fd, CONFIG_PORT0, 0x0000);

	while(1)
	{
		int i;
		for(i=0; i<10; i++)
		{
			wiringPiI2CWriteReg16(fd, OUT_PORT0, (aFndData[i]<<8|fndSelect);
			delay(1000);
		}
	}
	return 0;
}
