#include"inc.h"
/*****************
���ƣ�IR_REC
���ܣ�ң�ؽ���
*****************/
#define TEST
//
#define IR_BYTE 32 //����32λ
#define IR_SART 0x30//��ʼ��
#define IR_STOP 0x91//������1
/*
INT0----ң���ź�����
send_data �������͵�PC�������ݸ�ʽ��
����1,2�ż���TEST1���ص����������£�
/**01***�����룺00 FF 90 6F�� 
90 30
04 04 04 04 04 04 04 04 04 08 08 08 08 08 08 08 
08 04 04 07 04 04 04 04 04 06 08 04 07 08 08 08
91 28
/**02***�����룺00 FF B8 47 ��
E0 30 
04 04 04 04 04 04 04 04 04 08 08 08 08 08 08 08 
08 04 07 08 08 04 04 04 04 06 04 04 04 07 08 08 
91 28 
/*.........*/
/*--------------------*/
void IR_REC() interrupt 0
{	
	UR i;
	static bit STR=0;
	static UR count=0;//����λ����
	static UR IR_time;
	/****************/
	TR0=0;
	if(TL0>200)
	TH0+=1;
	IR_time=TH0;
	TH0=TL0=0;
	TR0=1;
	/***********/
	#ifdef TEST
	if(IR_time==IR_STOP)//���ս������������ݵ�PC�鿴
	{
		if(send_data)
		{ com(&IR_4_DATA,4);}
	}
	/*TEST1*/
	if(!send_data)//���ڲ�������,���������ȡ�����ұ������,���磺��ʼ������/�͵�ƽ���������ȣ�
	{
		com(&IR_time,1);//�����͵�PC����ʾ
	}
	#endif
	/*----------*/
	if((IR_time>2)&&(IR_time<5))//2-5 Ϊ "0"
	{	IR_time=0;}
	else if((IR_time>4)&&(IR_time<9))//5-9 Ϊ "1"
	{IR_time=0x01;}
	else//������
	{	
		STR=0;count=0;
		if(IR_SART==IR_time)//��ʼ
		{
			for(i=0;i<4;i++)//���ջ�������
			{IR_4_DATA[i]=0;}
			STR=1;
		}
		return;
	}
	/*----------*/
	if(STR)//��⵽��ʼλ
	{
		if(count<IR_BYTE)//����IR_BYTEλ
		{	
			IR_4_DATA[count/8]<<=1;
			IR_4_DATA[count/8]|=IR_time;
		}
		count++;
	}	
}
#undef TEST
/********/
void main()
{	sys_initial();
	while(1)
	{
		;
	}
}