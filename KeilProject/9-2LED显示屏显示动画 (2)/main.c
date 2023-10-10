#include <REGX52.H>
#include "Timer0.h"
#include "Key.h"
#include <INTRINS.H>
unsigned char KeyNum,LEDMode;
//中断函数,程序会自动跳转到中断函数处
//即使没有定义，1毫秒中断一次
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TH0=0xFC;
	TL0=0x18;//设置定时初值
	T0Count++;
  if(T0Count>=500)
	{
	  //重新赋初值
		T0Count=0;
	  if(LEDMode==0)
		{
		P2=_crol_(P2,1);//这个函数的意思就是左移一位
		}
		if(LEDMode==1) P2=_cror_(P2,1);//右移一位
	}
}
void main()
{
	P2=0xFE;
	Timer0_Init();
  while(1)
	{
		KeyNum=Key();
		if(KeyNum)
		{
		 if(KeyNum==1)
		 {
		   LEDMode++;
			 if(LEDMode>=2)
			 {
			   LEDMode=0;
			 }
		  }			 
		}
	}
}
