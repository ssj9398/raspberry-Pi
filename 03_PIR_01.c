#include <stdio.h>
#include <wiringPi.h>

const int pinPir = 24;

int main(void)
{
	wiringPiSetupGpio();

	pinMode(pinPir, INPUT);
	while(1)
	{
		if(!digitalRead(pinPir))
		{
			printf("Detected\n");
			delay(500);
		}
	}
	return 0;
}
