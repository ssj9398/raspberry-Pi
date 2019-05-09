#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define LIGHT_I2C_ADDR		0x23

#define LIGHT_I2C_POWER_DOWN	0x00
#define LIGHT_I2C_POWER_ON	0x01
#define LIGHT_I2C_RESET		0x07
#define LIGHT_I2C_CON_HR_MODE	0x10

int fd;

int main(void)
{
	float lightValue = 0.0;
	int aData[2];
	int i;
	int value;

	if((fd = wiringPiI2CSetup(LIGHT_I2C_ADDR))<0)
	{
		return -1;
	}

	wiringPiI2CWrite(fd, LIGHT_I2C_RESET);
	delay(50);

	while(1)
	{
		wiringPiI2CWrite(fd, LIGHT_I2C_CON_HR_MODE);
		delay(260);

	for(i=0; i<2; i++)
	{
		aData[i] = wiringPiI2CRead(fd);
	}

	value = (aData[0]<<8)+aData[1];
	lightValue = (int)value/1.2;

	printf("LIGHT : %.1f\n", (float)lightValue);
	delay(1000);
	}
	return 0;
}



