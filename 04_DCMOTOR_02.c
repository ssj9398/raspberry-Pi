#include <stdio.h>
#include <wiringPi.h>

const int pinEnable = 12;
const int pinPositive = 4;
const int pinNegative = 25;
const int aPinSwitch[2] = {6,5};

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

	while(1)
	{
		if(digitalRead(aPinSwitch[0]))
		{
			digitalWrite(pinPositive, HIGH);
			digitalWrite(pinNegative, LOW);
			digitalWrite(pinEnable, HIGH);
		}
		else if(digitalRead(aPinSwitch[1]))
		{
			digitalWrite(pinEnable, LOW);
		}
	}
	return 0;
}
