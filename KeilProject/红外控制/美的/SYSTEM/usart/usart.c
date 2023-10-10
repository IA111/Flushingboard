#include "usart.h"
#include "sys.h"
#include "LED.h"
//重定义<fputc>函数
#if 1
#pragma import(__use_no_semihosting)
//标准库需要支持的函数
struct __FILE
{
	int handle;
};
FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
_sys_exit(int x)
{
	x=x;
}
//重定向fputc函数
int fputc(int ch,FILE *f)
{
	while(!(USART1->SR&1<<7));
	USART1->DR=(u8)ch;
	return ch;
}
int fgetc(FILE *f)
{
	while(!(USART1->SR&1<<5));
	return USART1->DR;
}
#endif
/*
函数功能：USART1 的初始化；
硬件连接：
		USART1_TX -> PA9 ;
		USART1_RX -> PA10 ;
	
*/
void Usart1_Init(u32 bound)
{
	//时钟使能
	RCC->APB2ENR |=1<<2;	//GPIOA
	RCC->APB2ENR |=1<<14;	//USART
	
	//端口模式
	GPIOA->CRH &=0xFFFFF00F;	//PA9复用推挽输出
	GPIOA->CRH |=0x000008B0;	//PA10上下拉或浮空；
	
	//串口复位
	RCC->APB2RSTR |=1<<14;
	RCC->APB2RSTR &=~(1<<14);
	//使能串口中断
	USART1->CR1 |=1<<5;
	USART1->CR1 |=1<<4;
	Set_NVICPriority(USART1_IRQn,1,1);
	
	USART1->BRR=72000000/bound;	//波特率设置
	USART1->CR1 |=1<<3;			//使能发送
	USART1->CR1 |=1<<2;			//使能接收
	
	USART1->CR1 |=1<<13;		//使能串口
	
}
//发送字符串
void Usart_SendStr(USART_TypeDef *Usartx,u8 *str )
{
	while(*str != '\0')
	{
		Usartx->DR=*str;
		while(!(Usartx->SR&1<<7));
		str++;
	}
}
//整数转字符串
void Usart_Send_integer(USART_TypeDef *Usartx,u32 data)
{
	u8 num[20];
	int i=0;
	int temp,m,n;
	if(!data)
	{
		num[i]=data + '0';
		i++;
	}
	while(data)
	{
		num[i]=data%10 + '0';
		data=data/10;
		i++;
	}
	num[i]='\n';
	num[i+1]='\0';
	m=0;
	n=i-1;
	while(m<n)
	{
		temp=num[m];
		num[m]=num[n];
		num[n]=temp;
		m++;
		n--;
	}
	Usart_SendStr(Usartx,num);
	
}
//发送数据，二进制显示
void Usart_Send_binary(USART_TypeDef *Usartx,u8 data)
{
	int i;
	u8 num[10];
	for(i=0;i<8;i++)
	{
		if(data&0x80)
		{
			num[i]='1';
		}
		else
		{
			num[i]='0';
		}	
		data=data<<1;
	}
	num[i]='\n';
	num[i+1]='\0';
	Usart_SendStr(Usartx,num);
}
//串口一中断
//void USART1_IRQHandler(void)
//{
//	u8 data;
//	while(!(USART1->SR & 1<<5));
//	data=USART1->DR;
//	USART1->DR=data;
//	//while(!(USART1->SR & 1<<7));
//	if(data=='1') LED1=1;
//	if(data=='2') LED1=0;
//	
//}
u8 Buffer[100];
u8 RXcount=0;
u8 Revflag=0;
void USART1_IRQHandler(void)
{
	u8 clear=clear;
	if((USART1->SR&1<<5)!=0)
	{
		Buffer[RXcount++]=USART1->DR;
	}
	else if((USART1->SR&1<<4)!=0)
	{
		clear=USART1->SR;
		clear=USART1->DR;
		Buffer[RXcount]='\0';
		Revflag=1;
	}
//	if(Revflag==1)
//		{
//			Revflag=0;
//			RXcount=0;
//			Usart_SendStr(USART1,Buffer);
//		}
}
