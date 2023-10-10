#include "key.h"
#include "delay.h"
/*
函数功能：按键初始化
硬件连接：
		KEY_UP -> PA.0
		KEY1   -> PE.4
		KEY2   -> PE.3
		KEY3   -> PE.2
*/

void Key_Init(void)
{
	//时钟使能
	RCC->APB2ENR |=1<<6;	//GPIOE
	RCC->APB2ENR |=1<<2;	//GPIOA
	
	//端口配置
	GPIOE->CRL &=0xFFF000FF;	//PE2-4
	GPIOE->CRL |=0x00088800;
	
	GPIOE->ODR |=7<<2;
	
	GPIOA->CRL &=0xFFFFFFF0;	//PA.0
	GPIOA->CRL |=0x00000008;
}
u8 Key_Scan(u8 mode)
{
	static u8 key_flag=1;
	if(mode)  key_flag=1;
	if(key_flag&&(KEY1==0 || KEY2==0 || KEY3==0 || KEY_UP==1))
	{
		delay_MS(5);
		key_flag=0;
		if(KEY1==0)	return 1;
		else if(KEY2==0)	return 2;
		else if(KEY3==0)	return 3;
		else if(KEY_UP==1)	return 4;
	}
	else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY_UP==0)
		key_flag=1;
	return 0;
}
u8 key_one(void)
{
	if(((GPIOE->IDR) & 0x0010)==0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
u8 key_two(void)
{
	if(((GPIOE->IDR) & 0x0008)==0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
u8 key_three(void)
{
	if(((GPIOE->IDR) & 0x0004)==0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
u8 key_up(void)
{
	if(((GPIOA->IDR) & 0x0001)==0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
