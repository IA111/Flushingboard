#include"inc.h"
/*****************
名称：IR_REC
功能：遥控接收
*****************/
#define TEST
//
#define IR_BYTE 32 //接收32位
#define IR_SART 0x30//起始符
#define IR_STOP 0x91//结束符1
/*
INT0----遥控信号输入
send_data 决定发送到PC机的数据格式；
按下1,2号键在TEST1处截到的数据如下：
/**01***（解码：00 FF 90 6F） 
90 30
04 04 04 04 04 04 04 04 04 08 08 08 08 08 08 08 
08 04 04 07 04 04 04 04 04 06 08 04 07 08 08 08
91 28
/**02***（解码：00 FF B8 47 ）
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
	static UR count=0;//接收位计数
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
	if(IR_time==IR_STOP)//接收结束，发送数据到PC查看
	{
		if(send_data)
		{ com(&IR_4_DATA,4);}
	}
	/*TEST1*/
	if(!send_data)//对于不明编码,可在这里截取数据找编码规律,诸如：起始符，高/低电平，结束符等！
	{
		com(&IR_time,1);//串口送到PC机显示
	}
	#endif
	/*----------*/
	if((IR_time>2)&&(IR_time<5))//2-5 为 "0"
	{	IR_time=0;}
	else if((IR_time>4)&&(IR_time<9))//5-9 为 "1"
	{IR_time=0x01;}
	else//错误码
	{	
		STR=0;count=0;
		if(IR_SART==IR_time)//起始
		{
			for(i=0;i<4;i++)//接收缓存清零
			{IR_4_DATA[i]=0;}
			STR=1;
		}
		return;
	}
	/*----------*/
	if(STR)//检测到起始位
	{
		if(count<IR_BYTE)//接收IR_BYTE位
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