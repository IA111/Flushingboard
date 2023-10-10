#include "time.h"
#include "usart.h"
/*
函数功能：定时器6初始化

基本定时器：TIM6，TIM7；
通用定时器：TIM2，TIM3，TIM4，TIME5；
高级定时器：TIM1，TIM8；
 72MHz/72 = 1MHz = 1us；
定时器公式：重装值=溢出时间*晶振频率/预分频系数
*/
//PSC预分频值，ARR重装载值
void Time6_Init(u32 Psc,u32 Arr)
{
	//红外引脚初始化 PB5
	RCC->APB2ENR |=1<<3;	
	GPIOB->CRH &=0XFFFFFF0F;
	GPIOB->CRH |=0X00000080;
	GPIOB->ODR |=1<<9;
	
	//初始化红外线的接收引脚
	RCC->APB2ENR|=1<<6; //PE6
	GPIOE->CRL&=0xF0FFFFFF;
	GPIOE->CRL|=0x03000000;
	
	
	//定时器6时钟使能
	RCC->APB1ENR |=1<<4;
	
	RCC->APB1RSTR |=1<<4;
	RCC->APB1RSTR &=~(1<<4);
	
	TIM6->PSC=Psc-1;
	TIM6->ARR=Arr;
	
	//先关闭定时器6
	TIM6->CR1 &=~(1<<0);
}
u8 IR_data[6]={1,1,1,1,1};
/*
函数功能：获取高电平持续的时间
*/
u32 GetTimeH(void)
{
	TIM6->CNT=0;
	TIM6->CR1 |=1<<0;
	while(IR);	//等待高电平时间
	TIM6->CR1&=~(1<<0);
	TIM6->SR=0;	//清除更新标志
	return TIM6->CNT;
}
/*
函数功能：获取低电平持续的时间
*/
u32 GetTimL(void)
{
	TIM6->CNT=0;
	TIM6->CR1|=1<<0;
	while(!IR);	//等待低电平时间
	TIM6->CR1&=~(1<<0);
	TIM6->SR=0;
	return TIM6->CNT;
}
/*
函数功能：NEC红外协议解码
返回值：返回0成功，其他值失败
*/
u8 GetInfrad(void)
{
	u32 time;
	u8 data=0;
	u8 i,j;
	
	time=GetTimL();
	if(time<3400||time>5410) return 1;
	time=GetTimeH();
	if(time<3500||time>5500) return 1;
	
	for(i=0;i<6;i++)
	{	for(j=0;j<8;j++)
		{
			time=GetTimL();
			if(time<320||time>520) return 1;//425
			time=GetTimeH();
			if(time>1500&&time<1800)//1758
			{
				
				data>>=1;
				data|=0x80;
			}
			else if(time>553&&time<753)//653
			{
				data>>=1;
			}
			else
			{
				return 1;
			}
		}
		IR_data[i]=data;	
	}
	//DelayUs(5500);
	return 0;	
}
/*****************红外编码***************************/
/*
函数功能：发送38KHz载波
函数形参：
			u8 flag：发送0还是发送1；
			u32 time：发送载波持续的时间；
*/

void Send38KHz(u8 flag,u32 time)
{
	u32 i;
	if(flag==1)
	{
		for(i=0;i<time/13;i++)//发送38KHz载波；发送1，对方接收的是0
		{
			IE=!IE;
			DelayUs(11);
		}	
	}
	else
	{
		IE=0;
		DelayUs(time);
	}
	
}

/*
函数功能：红外编码
函数形参：
			u8 user_dat：用户码
			u8 key_dat：数据码
*/
void NEC_Code(u8 user_dat,u8 key_dat)
{
	u8 i;
	u8 user_fan=~user_dat;
	u8 key_fan=~key_dat;
	//发送载波；高电平 9ms
	Send38KHz(1,4410);
	//发送低电平4.5ms
	Send38KHz(0,4500);
	//发送用户码
	for(i=0;i<8;i++)
	{
		Send38KHz(1,481);
		if(user_dat&0x01)
		{
			Send38KHz(0,1679);
		}
		else
		{
			Send38KHz(0,571);
		}
		user_dat>>=1;
	}
	//发送用户反码
	for(i=0;i<8;i++)
	{
		Send38KHz(1,560);
		if(user_fan&0x01)
		{
			Send38KHz(0,1680);
		}
		else
		{
			Send38KHz(0,560);
		}
		user_fan>>=1;
	}
	//发送数据码
	for(i=0;i<8;i++)
	{
		Send38KHz(1,560);
		if(key_dat&0x01)
		{
			Send38KHz(0,1680);
		}
		else
		{
			Send38KHz(0,560);
		}
		key_dat>>=1;
	}
	//发送数据码
	for(i=0;i<=8;i++)
	{
		Send38KHz(1,560);
		if(key_fan&0x01)
		{
			Send38KHz(0,1680);
		}
		else
		{
			Send38KHz(0,560);
		}
		key_fan>>=1;
	}
	DelayMs(10);
}

void MD_Code(u8 dat[])
{
	u8 i,j;
	u8 data;
//	printf(" %d  %d  %d  %d  %d  %d\r\n",dat[0],dat[1],dat[2],dat[3],dat[4],dat[5]);
	
	for(j=0;j<6;j++)
	{
		data=dat[j];
		
		for(i=0;i<8;i++)
		{
			Send38KHz(1,425);
			if(data&0x01)
			{
				Send38KHz(0,1758);
			}
			else
			{
				Send38KHz(0,653);
			}
			data>>=1;
		}
	}
}
