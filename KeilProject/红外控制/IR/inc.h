#include"reg52.h"
typedef unsigned char UR;
bit send_data=1;
UR IR_4_DATA[4];
/*****************
名称：sys_initial
功能：系统初始化
*****************/
void sys_initial()
{
	TMOD=0x01;
	IT0=1;//下降沿触发
	EA=1;EX0=1;
	/***********/
	send_data=1;//
}
/*****************
名称：com
功能：串口发送字符数据；
形参：TS=数据指针;n=字符长度
*****************/
void com(UR *TS,UR n)
{
	UR m;
	TMOD|=0X20;//定时方式2
	SCON=0x50; //串口方式1
	PCON=0x00;//波特率不倍增
	TH1=0XFD;
	TL1=0XFD;//9600
	TR1=1;//启动波特率发生器
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