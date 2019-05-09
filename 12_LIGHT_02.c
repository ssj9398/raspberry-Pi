#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define LIGHT_I2C_ADDR			0x23

#define LIGHT_I2C_POWER_DOWN		0x00
#define LIGHT_I2C_POWER_ON		0x01
#define LIGHT_I2C_RESET			0x07
#define LIGHT_I2C_CON_HR_MODE		0x10

#define FND_I2C_ADDR			0x21

#define OUT_PORT0			0x02
#define CONFIG_PORT0			0x06

const int aFndData[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0x3E, 0xE0, 0xFE, 0xF6};

const int aFndSelect[6] = {0x7E, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB};

int fd_FND;
int fd_LIGHT;

void displayNumber(float number)
{
	int i;
	int aPosition[6] = {0, };
	printf("%.2f\n", number);

	aPosition[0] = (int)number/1000;
	aPosition[1] = (int)number%1000/100;
	aPosition[2] = (int)number%1000%100/10;
	aPosition[3] = (int)number%10;
	aPosition[4] = (int)(number*10)%10;
	aPosition[5] = (int)(number*100)%10;

	for(i=0; i<6; i++)
	{
		int temp = (aFndData[aPosition[i]]<<8 |aFndSelect[i]);

	if(i==3)
	{
		temp = temp | 0x0100;
	}

	wiringPiI2CWriteReg16(fd_FND, OUT_PORT0, temp);

	delay(600);
	}
}

int main(void)
{
	float lightValue = 0.0;
	int aData[2];
	int i;
	int value;

	if((fd_LIGHT = wiringPiI2CSetup(LIGHT_I2C_ADDR)) <0)
	{
		return -1;
	}

	if((fd_FND = wiringPiI2CSetup(FND_I2C_ADDR))<0)
	{
		return -1;
	}

	wiringPiI2CWriteReg16(fd_FND, CONFIG_PORT0, 0x0000);
	wiringPiI2CWrite(fd_LIGHT, LIGHT_I2C_RESET);
	delay(50);

	wiringPiI2CWrite(fd_LIGHT,LIGHT_I2C_CON_HR_MODE);
	delay(260);

	while(1)
	{
		for(i=0; i<2; i++)
		{
			aData[i] = wiringPiI2CRead(fd_LIGHT);
		}

		value =(aData[0]<<8)+aData[1];
		lightValue = (float)value/1.2;

		displayNumber(lightValue);
	}
	return 0;
}

	

