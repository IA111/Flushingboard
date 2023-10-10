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
//TIM_Delay��ʼ��
void Delay_Init(void)
{
		//����ʱ��
	RCC->APB1ENR|=1<<5; //��ʱ��7
	
	RCC->APB1RSTR|=1<<5; //������λʱ��
	RCC->APB1RSTR&=~(1<<5); //�رո�λʱ��
}
void DelayMs(u32 time)
{
	TIM7->PSC=7200-1;//Ԥ��Ƶ��cnt+1ʱ����0.1ms
	TIM7->ARR=time*10;
	TIM7->CNT=0;
	TIM7->CR1|=1<<0; //������ʱ��
	while(TIM7->CNT<TIM7->ARR); //�ȴ�ʱ�䵽��
	TIM7->CR1&=~(1<<0); //�رն�ʱ��
	TIM7->SR=0;
}

void DelayUs(u32 time)
{
		TIM7->PSC=72-1;//Ԥ��Ƶ��cnt+1ʱ����0.1ms
	  TIM7->ARR=time;
	  TIM7->CNT=0;
	  TIM7->CR1|=1<<0; //������ʱ��
	  while(!(TIM7->SR&1<<0)); //�ȴ�ʱ�䵽��
		TIM7->CR1&=~(1<<0); //�رն�ʱ��
		TIM7->SR=0;
}

