#include <REGX52.H>
#include <intrins.h>
void Delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 205;
	k = 187;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void main()
{
	//方法一，第一种流水灯实现方式
 while(1)
{
  P2=0XFE;//建议流水灯原理 1111 1110
	Delay500ms();
	P2=0XFD;//建议流水灯原理 1111 1101
	Delay500ms();
	P2=0XFB;//建议流水灯原理 1111 1011
	Delay500ms();
	P2=0XF7;//建议流水灯原理 1111 0111
	Delay500ms();
	P2=0XEF;//建议流水灯原理 1110 1111
	Delay500ms();
	P2=0XDF;//建议流水灯原理 1101 1110
	Delay500ms();
	P2=0XBF;//建议流水灯原理 1011 1110
	Delay500ms();
	P2=0X7F;//建议流水灯原理 0111 1110
	Delay500ms();
}
}