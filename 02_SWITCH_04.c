#include <stdio.h>
#include <wiringPi.h>

const int aPinSwitch[2] = {6,5};
const int aPinLed[2] = {21,20};

int ledFlag1 = 0;
int ledFlag2 = 0;
void ledBlink1(void)
{
	if(ledFlag1 ==0)
	{
	digitalWrite(aPinLed[0], HIGH);
	ledFlag1 = 1;
	}
	else
	{
	digitalWrite(aPinLed[0], LOW);
	ledFlag1 = 0;
	}
}

void ledBlink2(void)
{
	if(ledFlag2==0)
	{
		digitalWrite(aPinLed[1], HIGH);
		ledFlag2 = 1;
	}
	else
	{
		digitalWrite(aPinLed[1], LOW);
		ledFlag2 = 0;
	}
}

int main(void)
{
	wiringPiSetupGpio();

	int i;
	for(i=0; i<2; i++)
	{	
		pinMode(aPinSwitch[i], INPUT);
		pinMode(aPinLed[i], OUTPUT);
	}
	wiringPiISR(aPinSwitch[0], INT_EDGE_RISING, ledBlink1);
	wiringPiISR(aPinSwitch[1], INT_EDGE_FALLING, ledBlink2);

	while(1)
	{
	}
	return 0;
}
