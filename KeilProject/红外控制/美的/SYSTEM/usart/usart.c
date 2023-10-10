#include "usart.h"
#include "sys.h"
#include "LED.h"
//�ض���<fputc>����
#if 1
#pragma import(__use_no_semihosting)
//��׼����Ҫ֧�ֵĺ���
struct __FILE
{
	int handle;
};
FILE __stdout;
//����_sys_exit()�Ա���ʹ�ð�����ģʽ
_sys_exit(int x)
{
	x=x;
}
//�ض���fputc����
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
�������ܣ�USART1 �ĳ�ʼ����
Ӳ�����ӣ�
		USART1_TX -> PA9 ;
		USART1_RX -> PA10 ;
	
*/
void Usart1_Init(u32 bound)
{
	//ʱ��ʹ��
	RCC->APB2ENR |=1<<2;	//GPIOA
	RCC->APB2ENR |=1<<14;	//USART
	
	//�˿�ģʽ
	GPIOA->CRH &=0xFFFFF00F;	//PA9�����������
	GPIOA->CRH |=0x000008B0;	//PA10�������򸡿գ�
	
	//���ڸ�λ
	RCC->APB2RSTR |=1<<14;
	RCC->APB2RSTR &=~(1<<14);
	//ʹ�ܴ����ж�
	USART1->CR1 |=1<<5;
	USART1->CR1 |=1<<4;
	Set_NVICPriority(USART1_IRQn,1,1);
	
	USART1->BRR=72000000/bound;	//����������
	USART1->CR1 |=1<<3;			//ʹ�ܷ���
	USART1->CR1 |=1<<2;			//ʹ�ܽ���
	
	USART1->CR1 |=1<<13;		//ʹ�ܴ���
	
}
//�����ַ���
void Usart_SendStr(USART_TypeDef *Usartx,u8 *str )
{
	while(*str != '\0')
	{
		Usartx->DR=*str;
		while(!(Usartx->SR&1<<7));
		str++;
	}
}
//����ת�ַ���
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
//�������ݣ���������ʾ
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
//����һ�ж�
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
