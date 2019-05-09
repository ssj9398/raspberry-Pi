#include <stdio.h>
#include <wiringPi.h>

const int pinIr = 19;

int main(void)
{
	wiringPiSetupGpio();

	pinMode(pinIr, INPUT);

	while(1)
	{
		if(!digitalRead(pinIr))
		{
			printf("Read\n");
			delay(100);
		}
	}
	return 0;
}
