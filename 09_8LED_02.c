#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define LED_I2C_ADDR  0x20

#define IN_PORT0      0X00
#define IN_PORT1      0x01
#define OUT_PORT0     0x02
#define OUT_PORT1     0x03
#define POLARITY_IVE_PORT0   0x04
#define POLARITY_IVE_PORT1   0x05
#define CONFIG_PORT0  0x06
#define CONFIG_PORT1  0x07

const int aLedData[8] ={0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

const int aPinSwitch[2] ={6,5};
int fd;
int interruptFlag = 0;

void ledAscending(void)
{
	interruptFlag = 0;
}

void ledDescending(void)
{
	interruptFlag = 1;
}

int main(void)
{
	wiringPiSetupGpio();

	if((fd = wiringPiI2CSetup(LED_I2C_ADDR)) <0)
	{
		return -1;
	}

	wiringPiI2CWriteReg16(fd, CONFIG_PORT1, 0x00);

	int i;
	for(i=0; i<2; i++)
	{
		pinMode(aPinSwitch[i], INPUT);
	}

	wiringPiISR(aPinSwitch[0], INT_EDGE_RISING, ledAscending);
	wiringPiISR(aPinSwitch[1], INT_EDGE_RISING, ledDescending);

	while(1)
	{
		if(interruptFlag %2==0)
		{
		for(i=0; i<8; i++)
		{
			wiringPiI2CWriteReg16(fd, OUT_PORT1, aLedData[i]);
			delay(100);
		}
	}
	else
	{
		for(i=7; i>=0; i--)
		{
			wiringPiI2CWriteReg16(fd, OUT_PORT1, aLedData[i]);
			delay(100);
		}
		}
	}
	return 0;
}



















