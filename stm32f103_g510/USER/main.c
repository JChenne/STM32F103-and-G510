#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "usart3.h"
#include "GPS.h"
#include "timer.h"
#include "gizwits_product.h"
#include "common.h"
#include "led.h"
extern char a[100];

dataPoint_t currentDataPoint;

void Gizwits_Init(void)
{
	TIM3_Int_Init(9,7199);//1MSϵͳ��ʱ
  usart3_init(9600);//G510��ʼ��
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));//�豸״̬�ṹ���ʼ��
	gizwitsInit();//��������ʼ��
}
void userHandle(void)
{ 
	currentDataPoint.valueGPRS[0]= a[0]- 48 ; //3
	currentDataPoint.valueGPRS[1]= a[1]- 48 ; //9
	currentDataPoint.valueGPRS[2]= a[2]- 48 ; //5
	currentDataPoint.valueGPRS[3]= a[3]- 48 ; //4
	currentDataPoint.valueGPRS[4]= a[4]- 48 ;
	currentDataPoint.valueGPRS[5]= a[5]- 48 ;
	currentDataPoint.valueGPRS[6]= a[6]- 48 ;
	currentDataPoint.valueGPRS[7]= a[7]- 48 ;
	currentDataPoint.valueGPRS[8]= a[8]- 48 ;
	currentDataPoint.valueGPRS[9]= a[9]- 48 ;

	currentDataPoint.valueGPRS[10]= a[10]- 48 ; //1
	currentDataPoint.valueGPRS[11]= a[11]- 48 ; //1
	currentDataPoint.valueGPRS[12]= a[12]- 48 ; //9
	currentDataPoint.valueGPRS[13]= a[13]- 48 ; //3
	currentDataPoint.valueGPRS[14]= a[14]- 48 ; //0
	currentDataPoint.valueGPRS[15]= a[15]- 48 ;
	currentDataPoint.valueGPRS[16]= a[16]- 48 ;
	currentDataPoint.valueGPRS[17]= a[17]- 48 ;
	currentDataPoint.valueGPRS[18]= a[18]- 48 ;
	currentDataPoint.valueGPRS[19]= a[19]- 48 ;
	currentDataPoint.valueGPRS[20]= a[20]- 48 ;



	printf("choose_1 : %d \n",currentDataPoint.valuechoose_1); 
	printf("choose_2 : %d \n",currentDataPoint.valuechoose_2);
//	printf("pressure : %d \n",currentDataPoint.valuepressure) ;
	printf("switch : %d \n",currentDataPoint.valueswitch);
	printf("card : %d \n",currentDataPoint.valuecard);
	
	//�ܿ���
	if(currentDataPoint.valueswitch == 1)  
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
	}
	if(currentDataPoint.valueswitch == 0)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		currentDataPoint.valuechoose_1 = 0;
		currentDataPoint.valuechoose_2 = 0;
		currentDataPoint.valueswitch = 0;
		currentDataPoint.valuecard = 0;
	}
	
	//���
		if(currentDataPoint.valuechoose_2 == 1)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	}
	
	if(currentDataPoint.valuechoose_1 == 1)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_2);
	}

	if(currentDataPoint.valuechoose_1 == 0)
	{	
		GPIO_SetBits(GPIOC,GPIO_Pin_2);
	}
	
	if(currentDataPoint.valuechoose_2 == 0)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_1);
	}
	
	
	//�Ÿ迪��
	if(currentDataPoint.valuechoose_1 == 1 | currentDataPoint.valuechoose_2 == 1) 
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_3);
	}
	if(currentDataPoint.valuechoose_1 == 0 && currentDataPoint.valuechoose_2 == 0)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	}
	
	//�����û�п�
	if (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5) == 1)     
	{
		currentDataPoint.valuecard  = 1;
	}
	if (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5) == 0)
	{
		currentDataPoint.valuecard  = 0;
	}
		
}


int main(void)
{	

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//�������ȼ�
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
	delay_init();
	Init_LEDpin();
	clrStruct();
	Gizwits_Init();         //Э���ʼ��
	while(1)
	{
		parseGpsBuffer();
		printGpsBuffer();
		userHandle();//�û��ɼ�
    gizwitsHandle((dataPoint_t *)&currentDataPoint);//Э�鴦��
	  delay_ms(50);
	}
}
