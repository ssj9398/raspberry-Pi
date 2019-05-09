#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define SERVO_I2C_ADDR 		0x20

#define OUT_PORT0 		0x02
#define CONFIG_PORT0		0x06

const int period = 20000;
const int pinservoUD = 0x01;
const int pinservoLR = 0x02;

int fd;

int main(void)
{
	if((fd = wiringPiI2CSetup(SERVO_I2C_ADDR)) < 0)
	{
		return -1;
	}

	wiringPiI2CWriteReg16(fd, CONFIG_PORT0, 0x00);

	int i;
	wiringPiSetupGpio();

	while(1)
	{
		for(i=0; i<50; i++)
		{
			wiringPiI2CWriteReg16(fd,OUT_PORT0,pinservoUD);
			delayMicroseconds(50);
			wiringPiI2CWriteReg16(fd, OUT_PORT0, 0x00);
			delayMicroseconds(period-50);
		}

		for(i=0; i<50; i++)
		{
			wiringPiI2CWriteReg16(fd, OUT_PORT0,pinservoUD);
			delayMicroseconds(600);
			wiringPiI2CWriteReg16(fd, OUT_PORT0, 0x00);
			delayMicroseconds(period-600);
		}

		for(i=0; i<50; i++)
		{
			wiringPiI2CWriteReg16(fd, OUT_PORT0, pinservoUD);
			delayMicroseconds(1500);
			wiringPiI2CWriteReg16(fd, OUT_PORT0, 0x00);
			delayMicroseconds(period-1500);
		}

		for(i=0; i<50; i++)
		{
			wiringPiI2CWriteReg16(fd, OUT_PORT0, pinservoUD);
			delayMicroseconds(50);
			wiringPiI2CWriteReg16(fd, OUT_PORT0, 0x00);
			delayMicroseconds(period-50);
		}

		for(i=0; i<50; i++)
		{
			wiringPiI2CWriteReg16(fd, OUT_PORT0, pinservoUD);
			delayMicroseconds(1000);
			wiringPiI2CWriteReg16(fd, OUT_PORT0, 0x00);
			delayMicroseconds(period-1000);
		}
		for(i=0; i<50; i++)
		{
			wiringPiI2CWriteReg16(fd, OUT_PORT0, pinservoUD);
			delayMicroseconds(2000);
			wiringPiI2CWriteReg16(fd, OUT_PORT0, 0x00);
			delayMicroseconds(period-2000);
		}

		system("raspistill -t 5000 -o image2.jpg");

		}
		return 0;
}
