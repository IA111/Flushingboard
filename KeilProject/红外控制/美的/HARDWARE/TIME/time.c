#include "time.h"
#include "usart.h"
/*
�������ܣ���ʱ��6��ʼ��

������ʱ����TIM6��TIM7��
ͨ�ö�ʱ����TIM2��TIM3��TIM4��TIME5��
�߼���ʱ����TIM1��TIM8��
 72MHz/72 = 1MHz = 1us��
��ʱ����ʽ����װֵ=���ʱ��*����Ƶ��/Ԥ��Ƶϵ��
*/
//PSCԤ��Ƶֵ��ARR��װ��ֵ
void Time6_Init(u32 Psc,u32 Arr)
{
	//�������ų�ʼ�� PB5
	RCC->APB2ENR |=1<<3;	
	GPIOB->CRH &=0XFFFFFF0F;
	GPIOB->CRH |=0X00000080;
	GPIOB->ODR |=1<<9;
	
	//��ʼ�������ߵĽ�������
	RCC->APB2ENR|=1<<6; //PE6
	GPIOE->CRL&=0xF0FFFFFF;
	GPIOE->CRL|=0x03000000;
	
	
	//��ʱ��6ʱ��ʹ��
	RCC->APB1ENR |=1<<4;
	
	RCC->APB1RSTR |=1<<4;
	RCC->APB1RSTR &=~(1<<4);
	
	TIM6->PSC=Psc-1;
	TIM6->ARR=Arr;
	
	//�ȹرն�ʱ��6
	TIM6->CR1 &=~(1<<0);
}
u8 IR_data[6]={1,1,1,1,1};
/*
�������ܣ���ȡ�ߵ�ƽ������ʱ��
*/
u32 GetTimeH(void)
{
	TIM6->CNT=0;
	TIM6->CR1 |=1<<0;
	while(IR);	//�ȴ��ߵ�ƽʱ��
	TIM6->CR1&=~(1<<0);
	TIM6->SR=0;	//������±�־
	return TIM6->CNT;
}
/*
�������ܣ���ȡ�͵�ƽ������ʱ��
*/
u32 GetTimL(void)
{
	TIM6->CNT=0;
	TIM6->CR1|=1<<0;
	while(!IR);	//�ȴ��͵�ƽʱ��
	TIM6->CR1&=~(1<<0);
	TIM6->SR=0;
	return TIM6->CNT;
}
/*
�������ܣ�NEC����Э�����
����ֵ������0�ɹ�������ֵʧ��
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
/*****************�������***************************/
/*
�������ܣ�����38KHz�ز�
�����βΣ�
			u8 flag������0���Ƿ���1��
			u32 time�������ز�������ʱ�䣻
*/

void Send38KHz(u8 flag,u32 time)
{
	u32 i;
	if(flag==1)
	{
		for(i=0;i<time/13;i++)//����38KHz�ز�������1���Է����յ���0
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
�������ܣ��������
�����βΣ�
			u8 user_dat���û���
			u8 key_dat��������
*/
void NEC_Code(u8 user_dat,u8 key_dat)
{
	u8 i;
	u8 user_fan=~user_dat;
	u8 key_fan=~key_dat;
	//�����ز����ߵ�ƽ 9ms
	Send38KHz(1,4410);
	//���͵͵�ƽ4.5ms
	Send38KHz(0,4500);
	//�����û���
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
	//�����û�����
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
	//����������
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
	//����������
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
