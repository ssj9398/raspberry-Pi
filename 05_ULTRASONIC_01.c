#include <stdio.h>
#include <wiringPi.h>

const int pinEcho = 1;
const int pinTrigger = 0;

int main(void)
{
	wiringPiSetupGpio();

	pinMode(pinEcho, INPUT);
	pinMode(pinTrigger, OUTPUT);

	digitalWrite(pinTrigger, LOW);
	delay(30);

	while(1)
	{
		digitalWrite(pinTrigger, HIGH);
		delayMicroseconds(20);
		digitalWrite(pinTrigger, LOW);

		while(digitalRead(pinEcho)==LOW);
		long startTime = micros();

		while(digitalRead(pinEcho)==HIGH);
		long endTime = micros()-startTime;

		int distance = endTime / 58;

		printf("Distance:%d\n",distance);
		delay(1000);
	}
	return 0;
}
