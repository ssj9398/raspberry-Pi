#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <lcd.h>

#define SHT20_I2C_ADDR			0x40

#define SHT20_I2C_CMD_MEASURE_TEMP	0xF3

#define SHT20_I2C_CMD_MEASURE_HUMI	0xF5
#define SHT20_SOFT_RESET		0xFE

const int pinEnable = 12;
const int pinPositive = 4;
const int pinNegative = 25;

int fd;

int main(void)
{
	float temp = 0.0;
	float humi = 0.0;

	int aData[2];
	int value;
	int i;

	wiringPiSetupGpio();

	pinMode(pinEnable, OUTPUT);
	pinMode(pinPositive, OUTPUT);
	pinMode(pinNegative, OUTPUT);

	int lcd = lcdInit(2, 16, 4, 16, 26, 18, 27, 22, 23, 0, 0, 0, 0);

	if((fd = wiringPiI2CSetup(SHT20_I2C_ADDR))<0)
	{
		return -1;
	}

	wiringPiI2CWrite(fd, SHT20_SOFT_RESET);

	lcdClear(lcd);
	delay(50);

	while(1)
	{
		wiringPiI2CWrite(fd, SHT20_I2C_CMD_MEASURE_TEMP);
		delay(260);

	for(i=0; i<2; i++)
	{
		aData[i] = wiringPiI2CRead(fd);
	}
	value = aData[0]<<8|aData[1];
	temp = -46.85 + 175.72/65536*(int)value;

	wiringPiI2CWrite(fd, SHT20_I2C_CMD_MEASURE_HUMI);
	delay(260);

	for(i=0; i<2; i++)
	{
		aData[i] = wiringPiI2CRead(fd);
	}

	value = aData[0]<<8|aData[1];
	humi = -6.0 + 125.0/65536*(int)value;

	lcdPosition(lcd,0,0);
	lcdPrintf(lcd, "Temp:%.1f[C]", temp);

	lcdPosition(lcd, 0,1);
	lcdPrintf(lcd, "Humi:%.1f[%]",humi);
	delay(500);

	if(temp>=30.0 ||humi >=50.0)
	{
		digitalWrite(pinEnable, HIGH);
		digitalWrite(pinPositive, HIGH);
		digitalWrite(pinNegative, LOW);
	}
	else
	{
		digitalWrite(pinEnable, LOW);
	}
	}
	return 0;
	}

