#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <malloc.h>
#include <time.h>

#define SHT20_I2C_ADDR 			0x40
#define SHT20_I2C_CMD_MEASURE_TEMP 	0xF3
#define SHT20_I2C_CMD_MEASURE_HUMI 	0xF5
#define SHT20_SOFT_RESET 		0xFE
#define LIGHT_I2C_ADDR			0x23
#define LIGHT_I2C_POWER_DOWN		0x00
#define LIGHT_I2C_POWER_ON		0x01
#define LIGHT_I2C_RESET			0x07
#define LIGHT_I2C_CON_HR_MODE		0x10
#define LED_I2C_ADDR			0x20
#define IN_PORT0 			0x00
#define IN_PORT1			0x01
#define OUT_PORT0			0x02
#define OUT_PORT1			0x03
#define POLARITY_IVE_PORT0		0x04
#define POLARITY_IVE_PORT1		0x05
#define CONFIG_PORT0			0x06
#define CONFIG_PORT1			0x07

typedef struct tempbyclothes
{
	float temp;            //온도
	float humi;           //습도
	float light;           //광량
	struct tempbyclothes *link;
} Tempbyclothes;

int addHead(Tempbyclothes **head, float temp, float humi, float light);
Tempbyclothes *newNode(float temp, float humi, float light);
int removeHead(Tempbyclothes **head);
int removeAll(Tempbyclothes **head);
void printList(Tempbyclothes *head);
int saveList(char *fileName, Tempbyclothes*head);
int saveNode(FILE *fp, Tempbyclothes *node);
int getCount(Tempbyclothes *head);

int fd,fd2,fd3;
int main(void)
{
	Tempbyclothes *head = NULL;          //헤더 널값
	float temp = 0.0;
	float humi = 0.0;
	float light;
	int aData[2];
	int value;
	int i,j,k;
	float lightValue = 0.0;
	int aData2[2];
	int value2;
	int count=0,cnt=0;
	time_t timer;
	struct tm*t;
	const int led[8]={0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

if((fd = wiringPiI2CSetup(SHT20_I2C_ADDR)) < 0)   //I2C 시스템 초기화 설정
	{
		return -1;
	}

	wiringPiI2CWrite(fd, SHT20_SOFT_RESET);          //SHT20 센서 초기화 설정
//delay(50);

if((fd2 = wiringPiI2CSetup(LIGHT_I2C_ADDR))<0)  //I2C 시스템 초기화 설정
	{
		return -1;
	}

	wiringPiI2CWrite(fd2, LIGHT_I2C_RESET);      //LIGHT 센서 초기화 설정
//delay(50);

if((fd3 = wiringPiI2CSetup(LED_I2C_ADDR)) < 0)
	{
		return -1; 
	}

	wiringPiI2CWriteReg16(fd3, CONFIG_PORT1, 0x00);

while(1)
{
	wiringPiI2CWrite(fd, SHT20_I2C_CMD_MEASURE_TEMP);	//온도 측정 모드
	delay(260);


	for(i=0; i<2; i++)		//측정한 데이터 저장
	{
		aData[i] = wiringPiI2CRead(fd);
	}
	value = aData[0] << 8 | aData[1];
	temp = -46.85 + 175.72/65536*(int) value;	//측정한 데이터로 온도계산

	wiringPiI2CWrite(fd, SHT20_I2C_CMD_MEASURE_HUMI);
	delay(260);

	for(i=0; i<2; i++)                       //측정한 데이터 저장
	{
		aData[i] = wiringPiI2CRead(fd);
	}

	value = aData[0] << 8 | aData[1];
	humi = -6.0 + 125.0/65536*(int)value;		//측정한 데이터로 습도계산

	delay(500);

	if(temp>28)                          //온도에 따른 옷차림 출력
	{
		printf("Temp : %.1lf  short sleeve and pants\n",temp);
	}

	else if(temp>25)
	{
		printf("Temp : %.1lf short sleeve and pants thin shirt\n",temp);
	}

	else if(temp>23)
	{
		printf("Temp : %.1lf long tee blue jeans thin cardigan\n",temp);
	}

	else if(temp>18)
	{
		printf("Temp : %.1lf knit man-to-man thin jacket\n",temp);
	}

	else if(temp>13)
	{
		printf("Temp : %.1lf jacket cardigan field jacket\n",temp);
	}

	else if(temp>9)
	{
		printf("Temp : %.1lf jacket trenchcoat stockings\n",temp);
	}

	else if(temp>5)
	{
		printf("Temp : %.1lf coat heat-tech leggings\n",temp);
	}
	else
		printf("Temp : %.1lf padding heavycoat muffler\n",temp);


	wiringPiI2CWrite(fd2, LIGHT_I2C_CON_HR_MODE);	//빛 측정모드
	delay(260);

	for(j=0; j<2; j++)			//데이터 저장
	{
		aData2[j] = wiringPiI2CRead(fd2);
	}

	value2 = (aData2[0]*255) + aData2[1];		//빛 세기 구하기
	lightValue = (int)value2 / 1.2;
	

	if(lightValue>400)			//빛 세기에 따른 선크림 권장
        {
		
                printf("LIGHTVALUE :  %.1lf  suncream 100\n",lightValue);
        }

        else if(lightValue>200)
        {
		
                 printf("LIGHTVALUE :  %.1lf suncream 50\n", lightValue);
        }

        else
		
                printf("LIGHTVALUE :  %.1lf suncream 10\n", lightValue);
	delay(2000);

	timer = time(NULL);
	t = localtime(&timer);

	//if(t->tm_sec%2==0)
	//{
		addHead(&head,temp,humi,lightValue);
		printList(head);
		count++;
	//}
	(saveList("project2_1.txt",head));
	if(count%3==0)
	{
		removeAll(&head);
	}
	printf("\n");
	delay(200);



	if(temp>30&&humi>70)
	{
		for(k=0;k<8;k++)
		{
			wiringPiI2CWriteReg16(fd3, OUT_PORT1, led[k]);
		}
	}

	else if(temp>28.5&&humi>60)
	{
		for(k=0;k<7;k++)
		{
			wiringPiI2CWriteReg16(fd3, OUT_PORT1, led[k]);
		}
	}
	else if(temp>26&&humi>45)
	{
		for(k=0;k<6;k++)
		{
			wiringPiI2CWriteReg16(fd3, OUT_PORT1, led[k]);
		}
	}
	else if(temp>24&&humi>40)
	{
		for(k=0;k<4;k++)
		{
			wiringPiI2CWriteReg16(fd3, OUT_PORT1, led[k]);
		}
	}
	else
		for(k=0;k<2;k++)
		{
			wiringPiI2CWriteReg16(fd3, OUT_PORT1, led[k]);
		}
	//delay(1000);
	
}
	return 0;
}




int addHead(Tempbyclothes **head, float temp, float humi, float light)
{
	Tempbyclothes *node = newNode(temp,humi,light);
	if(node==NULL) return FALSE;
	if(head!=NULL)
	{
		node->link= *head;
		*head=node;
	}
	return TRUE;
}

Tempbyclothes *newNode(float temp, float humi,float light)
{
	Tempbyclothes *node = (Tempbyclothes *) malloc(sizeof(Tempbyclothes));
	node->temp=temp;
	node->humi=humi;
	node->light=light;
	node->link=NULL;

	return node;
}

int removeHead(Tempbyclothes **head)
{
	if(*head ==NULL) return FALSE;

	Tempbyclothes *node=*head;
	*head=node->link;

	free(node);
	return TRUE;
}

int removeAll(Tempbyclothes **head)
{
	if(head==NULL) return FALSE;
	while(*head !=NULL) removeHead(head);
	return TRUE;
}

void printList(Tempbyclothes *head)
{
	Tempbyclothes *current = head;
	int position = 0;
	int i=0;
	while(current != NULL)
	{
		i++;
		printf("(%d) %.1lf %.1lf %.1lf \n",i, current->temp, current->humi,
		current->light);
		current = current ->link;
	}
	return;
}

int saveList(char *fileName, Tempbyclothes*head)
{
	int i=0;
	int cnt = getCount(head);
	Tempbyclothes *current = head;
	FILE * fp = fopen(fileName,"w+");
	for(i=0; i<cnt; i++)
	{
		if(!saveNode(fp, current))
		{
			printf("(!) save node failed...\n");
			return FALSE;
		}
		current = current->link;
	}
	fclose(fp);
	return TRUE;
}

int saveNode(FILE *fp, Tempbyclothes*node)
{
	if(fp ==NULL) return FALSE;
	if(node ==NULL) return FALSE;

	char buf[255]="";
	sprintf(buf," %.1lf %.1lf %.1lf\n", node ->temp, node->humi, node->light);
	fputs(buf, fp);

	return TRUE;
}

int getCount(Tempbyclothes *head)
{
	int count = 0;
	Tempbyclothes * current = head;
	while(current!=NULL)
	{
		current = current ->link;
		count++;
	}
	return count;
}
