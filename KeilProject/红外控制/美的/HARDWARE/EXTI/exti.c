#include "exti.h"
#include "led.h"
/*
函数功能：按键外部中断初始化
硬件连接：
		KEY_UP -> PA.0
		KEY1   -> PE.4
		KEY2   -> PE.3
		KEY3   -> PE.2
*/
void Exti_Init(void)
{
	//这里设置PA.0
	Key_Init();
	EXTI->IMR |= 1<<0;
	EXTI->RTSR |= 1<<0;
	Set_NVICPriority(EXTI0_IRQn,2,2);
	RCC->APB2ENR |= 1<<0;
	AFIO->EXTICR[0] &=~(0x0F<<0);	//数组【0】决定那部分IO号（0~15），分为四部分；
	AFIO->EXTICR[0] |=0x00<<0;		//0x00决定A~G；
	
}

void EXTI0_IRQHandler(void)
{
	if(Key_Scan(0)==4)
	{
		LED1=!LED1;
	}
	
	//EXTI->PR |=1<<0;
}

