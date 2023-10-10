#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "Nixie.h"
#include "Timer0.h"

//需要把电机的两根线接在D1和5V的口子上，蜂鸣器那里

//sbit LED=P2^0;   //LED LED=1 灯灭  =0 灯亮 
sbit Motor = P1^0;//电机端口  电机=1；电机转动，=0 电机停止转动
unsigned char Counter,Compare;

unsigned char KeyNumber,Speed;
void main()
{
	Timer0_Init();
	Compare=5;
    while(1)
  {
    KeyNumber=Key();
		if(KeyNumber==1)
		{
		 Speed++;
		if(Speed==4) Speed=0;
		if(Speed==0)Compare=0;
		if(Speed==1)Compare=50;
		if(Speed==2)Compare=75;
		if(Speed==3)Compare=100;
		}
		Nixie(1,Speed);
   }
}

void Timer0_Routine() interrupt 1
{
//每个一百微秒进入一次中断
	TH0=0xFf;
	TL0=0x9C;//设置定时初值
	Counter++;
	if(Counter>100)
	{
	 Counter=0;
	}
	if(Counter<Compare)
	{
		Motor=1;
	}else{
	  Motor=0;
	}
}