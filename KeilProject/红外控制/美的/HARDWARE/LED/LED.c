#include "led.h"
/*
函数功能：LED初始化；
硬件连接：
		LED1 -> PF7;
		LED2 -> PB5;
		LED3 -> PA8;
		LED4 -> PA1;
*/

void Led_Init(void)
{
	//1.时钟使能
	RCC->APB2ENR |=1<<3;	//GPIOB
	RCC->APB2ENR |=1<<2;	//GPIOA
	RCC->APB2ENR |=1<<7;	//GPIOF
	
	//2.端口配置
	GPIOB->CRL &=0xFF0FFFFF;	//PB.5
	GPIOB->CRL |=0x00300000;
	GPIOB->ODR |=1<<5;
	
	GPIOA->CRL &=0xFFFFFF0F;	//PA.1
	GPIOA->CRL |=0x00000030;
	GPIOA->ODR |=1<<1;
	
	GPIOA->CRH &=0xFFFFFFF0;	//PA.8
	GPIOA->CRH |=0x00000003;
	GPIOA->ODR |=1<<8;
	
	GPIOF->CRL &=0x0FFFFFFF;	//PF.7
	GPIOF->CRL |=0x30000000;
	GPIOF->ODR |=1<<7;
	
}
void Beep_Init(void)
{
	//时钟使能
	RCC->APB2ENR |=1<<3;
	
	GPIOB->CRH &=0xFFFFFFF0;
	GPIOB->CRH |=0x00000003;
}

