#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define SHT20_I2C_ADDR			0x40

#define SHT20_I2C_CMD_MEASURE_TEMP	0xF3
#define SHT20_I2C_CMD_MEASURE_HUMI	0xF5
#define SHT20_SOFT_RESET		0xFE

int fd;

int main(void)
{
	float temp = 0.0;
	float humi = 0.0;

	int aData[2];
	int value;
	int i;

	if((fd=wiringPiI2CSetup(SHT20_I2C_ADDR)) <0)
	{
		return -1;
	}

	wiringPiI2CWrite(fd, SHT20_SOFT_RESET);
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

	printf("Temp : %.1f\n",(float)temp);
	printf("Humi:%.1f\n",(float)humi);

	delay(1000);
	}
	return 0;
}

