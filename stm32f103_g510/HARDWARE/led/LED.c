#include "LED.h"

void Init_LEDpin(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PC端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_3|GPIO_Pin_1|GPIO_Pin_2;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //Pc5 设置成输入，默认下拉	，有卡时PC5为1 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOC,GPIO_Pin_13);					//初始化设置1
	
	GPIO_SetBits(GPIOC,GPIO_Pin_1);					//点歌1
	GPIO_SetBits(GPIOC,GPIO_Pin_2);					//点歌2
	
	GPIO_SetBits(GPIOC,GPIO_Pin_3);					//开关
	
}

