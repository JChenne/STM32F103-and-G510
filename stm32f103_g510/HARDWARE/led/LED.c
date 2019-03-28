#include "LED.h"

void Init_LEDpin(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PC�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_3|GPIO_Pin_1|GPIO_Pin_2;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //Pc5 ���ó����룬Ĭ������	���п�ʱPC5Ϊ1 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOC,GPIO_Pin_13);					//��ʼ������1
	
	GPIO_SetBits(GPIOC,GPIO_Pin_1);					//���1
	GPIO_SetBits(GPIOC,GPIO_Pin_2);					//���2
	
	GPIO_SetBits(GPIOC,GPIO_Pin_3);					//����
	
}

