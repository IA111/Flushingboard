#include "delay.h"
void delay_US(u32 time)	//360us
{
	u32 i,j;
	for(i=0;i<time;i++)
		for(j=0;j<72;j++);
}
void delay_MS(u32 time)
{
	u32 i,j,n;
	for(i=0;i<time;i++)
		for(j=0;j<100;j++)
			for(n=0;n<100;n++);
}
//TIM_Delay初始化
void Delay_Init(void)
{
		//开启时钟
	RCC->APB1ENR|=1<<5; //定时器7
	
	RCC->APB1RSTR|=1<<5; //开启复位时钟
	RCC->APB1RSTR&=~(1<<5); //关闭复位时钟
}
void DelayMs(u32 time)
{
	TIM7->PSC=7200-1;//预分频，cnt+1时间是0.1ms
	TIM7->ARR=time*10;
	TIM7->CNT=0;
	TIM7->CR1|=1<<0; //开启定时器
	while(TIM7->CNT<TIM7->ARR); //等待时间到达
	TIM7->CR1&=~(1<<0); //关闭定时器
	TIM7->SR=0;
}

void DelayUs(u32 time)
{
		TIM7->PSC=72-1;//预分频，cnt+1时间是0.1ms
	  TIM7->ARR=time;
	  TIM7->CNT=0;
	  TIM7->CR1|=1<<0; //开启定时器
	  while(!(TIM7->SR&1<<0)); //等待时间到达
		TIM7->CR1&=~(1<<0); //关闭定时器
		TIM7->SR=0;
}

