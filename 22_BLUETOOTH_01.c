#include <stdio.h>
#include <wiringPi.h>
#define BLUE_PORT "/dev/rfcomm0"
#define BAUD_RATE 115200
int main(void)
	{
		int dev;
		if((dev = serialOpen(BLUE_PORT, BAUD_RATE)) < 0)
		{
			return -1;
		}
		printf("Port Open.\n");
		serialFlush(dev);

	while(1)
	{
		char ch = serialGetchar(dev);

		if(ch=='x')
		{
			break;
		}
		else
		{
			fputc(ch, stderr);
			serialPutchar(dev, ch);
		}
	}
	printf("Port Closed.\n");
	serialClose(dev);

	return 0;
}
