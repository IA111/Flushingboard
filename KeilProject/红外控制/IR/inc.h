#include"reg52.h"
typedef unsigned char UR;
bit send_data=1;
UR IR_4_DATA[4];
/*****************
���ƣ�sys_initial
���ܣ�ϵͳ��ʼ��
*****************/
void sys_initial()
{
	TMOD=0x01;
	IT0=1;//�½��ش���
	EA=1;EX0=1;
	/***********/
	send_data=1;//
}
/*****************
���ƣ�com
���ܣ����ڷ����ַ����ݣ�
�βΣ�TS=����ָ��;n=�ַ�����
*****************/
void com(UR *TS,UR n)
{
	UR m;
	TMOD|=0X20;//��ʱ��ʽ2
	SCON=0x50; //���ڷ�ʽ1
	PCON=0x00;//�����ʲ�����
	TH1=0XFD;
	TL1=0XFD;//9600
	TR1=1;//���������ʷ�����
	EA=0;
	/////
	for(m=0;m<n;m++)
	{
		SBUF=*(TS+m);
    	while(!TI);
   	TI=0;
   }
	EA=1;
}