#include <REGX52.H>
#include <INTRINS.h>
#include "Delay1.h"
#include "Key.h"
#include "Nixie.h" 

//这个新的板子由于引脚冲突，所有不是视频中的P1口
sbit Buzzer=P2^5;

void Buzzer_Delay500us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 247;
	while (--i);
}

void Buzzer_time(unsigned int xms)
{
	  unsigned int i;
    for(i=0;i<xms*2;i++)
	{
	  Buzzer=!Buzzer;
		Buzzer_Delay500us();
	}
}