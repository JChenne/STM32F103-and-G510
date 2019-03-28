#include "usart.h"
#include "stm32f10x.h"
  char a[100];
	
void errorLog(int num)
{
	while (1)
	{
	  	printf("ERROR%d\r\n",num);
	}
}

void parseGpsBuffer()
{
	char *subString;
	char *subStringNext;
	char i = 0;
	if (Save_Data.isGetData)
	{
		Save_Data.isGetData = false;
		printf("**************\r\n");
//		printf(Save_Data.GPS_Buffer);

		
		for (i = 0 ; i <= 6 ; i++)
		{
			if (i == 0)
			{
				if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
					errorLog(1);	//解析错误
			}
			else
			{
				subString++;
				if ((subStringNext = strstr(subString, ",")) != NULL)
				{
					char usefullBuffer[2]; 
					switch(i)
					{
						case 1:memcpy(Save_Data.UTCTime, subString, subStringNext - subString);break;	//获取UTC时间
						case 2:memcpy(usefullBuffer, subString, subStringNext - subString);break;	//获取UTC时间
						case 3:memcpy(Save_Data.latitude, subString, subStringNext - subString);break;	//获取纬度信息
						case 4:memcpy(Save_Data.N_S, subString, subStringNext - subString);break;	//获取N/S
						case 5:memcpy(Save_Data.longitude, subString, subStringNext - subString);break;	//获取经度信息
						case 6:memcpy(Save_Data.E_W, subString, subStringNext - subString);break;	//获取E/W

						default:break;
					}

					subString = subStringNext;
					Save_Data.isParseData = true;
					if(usefullBuffer[0] == 'A')
						Save_Data.isUsefull = true;
					else if(usefullBuffer[0] == 'V')
						Save_Data.isUsefull = false;
				}
				else
				{
					errorLog(2);	//解析错误
				}
			}
		}
	}
}

void printGpsBuffer()
{

	if (Save_Data.isParseData)
	{
		Save_Data.isParseData = false;
		
//		printf("Save_Data.UTCTime = ");
//		printf(Save_Data.UTCTime);
//		printf("\r\n");

		if(Save_Data.isUsefull)
		{
			Save_Data.isUsefull = false;
			printf("Save_Data.latitude = ");
			printf(Save_Data.latitude);
			printf("\r\n");
			
			a[0] = *Save_Data.latitude;
			a[1] = *(Save_Data.latitude+1);
			a[2] = *(Save_Data.latitude+2);
			a[3] = *(Save_Data.latitude+3);
			a[4] = *(Save_Data.latitude+4);
			a[5] = *(Save_Data.latitude+5);
			a[6] = *(Save_Data.latitude+6);
			a[7] = *(Save_Data.latitude+7);
			a[8] = *(Save_Data.latitude+8);
			a[9] = *(Save_Data.latitude+9);
				
			printf("Save_Data.N_S = ");
			printf(Save_Data.N_S);
			printf("\r\n");

			printf("Save_Data.longitude = ");
			printf(Save_Data.longitude);
			printf("\r\n");
			
			a[10] = *Save_Data.longitude;
			a[11] = *(Save_Data.longitude+1);
			a[12] = *(Save_Data.longitude+2);
			a[13] = *(Save_Data.longitude+3);
			a[14] = *(Save_Data.longitude+4);
			a[15] = *(Save_Data.longitude+5);
			a[16] = *(Save_Data.longitude+6);
			a[17] = *(Save_Data.longitude+7);
			a[18] = *(Save_Data.longitude+8);
			a[19] = *(Save_Data.longitude+9);
			a[20] = *(Save_Data.longitude+10);

			

			printf("Save_Data.E_W = ");
			printf(Save_Data.E_W);
			printf("\r\n");
			
		}
		else
		{
			printf("GPS DATA is not usefull!\r\n");
		}
		
	}
}
