#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

const int pinServo = 17;

int main(void)
{
	wiringPiSetupGpio();

	softPwmCreate(pinServo, 0, 200);

	while(1)
	{
		softPwmWrite(pinServo, 5);
		delay(1000);
		softPwmWrite(pinServo, 15);
		delay(1000);
		softPwmWrite(pinServo, 25);
		delay(1000);
		softPwmWrite(pinServo, 15);
		delay(1000);
	}
	return 0;
}
