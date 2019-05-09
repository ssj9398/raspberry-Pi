#include <stdio.h>
#include <wiringPi.h>
#include <lcd.h>

const int pinEcho = 1;
const int pinTrigger = 0;

int main(void)
{
	wiringPiSetupGpio();

	pinMode(pinEcho, INPUT);
	pinMode(pinTrigger, OUTPUT);

	int lcd = lcdInit(2, 16, 4, 16, 26, 18, 27, 22, 23, 0, 0, 0, 0);

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
	long endTime = micros() - startTime;

	int distance = endTime / 58;

	lcdClear(lcd);
	lcdPosition(lcd,0,0);
	lcdPuts(lcd, "Distance");

	lcdPosition(lcd, 0, 1);
	lcdPrintf(lcd, "%d cm", distance);

	delay(500);
	}
	return 0;
}
