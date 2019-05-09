#include <stdio.h>
#include <wiringPi.h>

const int pinEnable = 12;
const int pinPositive = 4;
const int pinNegative = 25;
const int aPinSwitch[2] = {6,5};

void motorSpin(void)
{
	digitalWrite(pinEnable, HIGH);
	digitalWrite(pinPositive, HIGH);
	digitalWrite(pinNegative, LOW);
}

void motorStop(void)
{
	digitalWrite(pinEnable, LOW);
}

int main(void)
{
	wiringPiSetupGpio();

	pinMode(pinEnable, OUTPUT);
	pinMode(pinPositive, OUTPUT);
	pinMode(pinNegative, OUTPUT);

	int i;

	for(i=0; i<2; i++)
	{
		pinMode(aPinSwitch[i], INPUT);
	}

	wiringPiISR(aPinSwitch[0], INT_EDGE_RISING, motorSpin);
	wiringPiISR(aPinSwitch[1], INT_EDGE_FALLING, motorStop);

	while(1)
	{
	}
	return 0;
}

	 
