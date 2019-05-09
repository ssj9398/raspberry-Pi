#include <stdio.h>
#include <wiringPi.h>

const int pinPir = 24;
const int aPinLed[2] = {21,20};

int main(void)
{
	wiringPiSetupGpio();

	pinMode(pinPir, INPUT);

	int i;
	for(i=0; i<2; i++)
	{
		pinMode(aPinLed[i], OUTPUT);
	}

	while(1)
	{
		if(!digitalRead(pinPir))
		{
			digitalWrite(aPinLed[0], LOW);
			digitalWrite(aPinLed[1], HIGH);
		}
		else
		{
			digitalWrite(aPinLed[0], HIGH);
			digitalWrite(aPinLed[1], LOW);
		}
		delay(500);
	}
	return 0;
}
