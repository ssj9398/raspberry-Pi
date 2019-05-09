#include <stdio.h>
#include <wiringPi.h>

const int pinEnable = 12;
const int pinPositive = 4;
const int pinNegative = 25;

int main(void)
{
	wiringPiSetupGpio();

	pinMode(pinEnable, OUTPUT);
	pinMode(pinPositive, OUTPUT);
	pinMode(pinNegative, OUTPUT);

	while(1)
	{
		digitalWrite(pinPositive, HIGH);
		digitalWrite(pinNegative, LOW);
		digitalWrite(pinEnable, HIGH);
		delay(2000);

		digitalWrite(pinEnable, LOW);
		delay(2000);

		digitalWrite(pinPositive, LOW);
		digitalWrite(pinNegative, HIGH);
		digitalWrite(pinEnable, HIGH);
		delay(2000);

		digitalWrite(pinEnable, LOW);
		delay(2000);
		}

	return 0;
}
