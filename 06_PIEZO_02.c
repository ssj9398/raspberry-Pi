#include <stdio.h>
#include <wiringPi.h>
#include <softTone.h>

const int pinPiezo = 13;
const int pinPir = 24;



const int aMelody[9] = {131, 147, 165, 175, 196, 208, 220, 247, 262};

int main(void)
{
	wiringPiSetupGpio();
	pinMode(pinPir, INPUT);
	softToneCreate(pinPiezo);

	while(1)
	{
		if(!digitalRead(pinPir))
		{
			softToneWrite(pinPiezo, aMelody[2]);
			delay(100);
			softToneWrite(pinPiezo, aMelody[0]);
			delay(100);
		}
		else
		{
			softToneWrite(pinPiezo, 0);
			delay(100);
		}
	}
	return 0;
 }
