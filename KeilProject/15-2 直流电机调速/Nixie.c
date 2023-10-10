#include <REGX52.H>
#include "Delay.h"
unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};


void Nixie(unsigned int Location,unsigned char Number)
{
	switch(Location)
	{
		//因为第一个数字显示，在数码管上是链接Y7引脚所以为111，所以是三个端口为111
	  case 1:P2_4=1;P2_3=1;P2_2=1; break;
	  case 2:P2_4=1;P2_3=1;P2_2=0; break;
		case 3:P2_4=1;P2_3=0;P2_2=1; break;
		case 4:P2_4=1;P2_3=0;P2_2=0; break;
		case 5:P2_4=0;P2_3=1;P2_2=1; break;
		case 6:P2_4=0;P2_3=1;P2_2=0; break;
		case 7:P2_4=0;P2_3=0;P2_2=1; break;
		case 8:P2_4=0;P2_3=0;P2_2=0; break;
	}
	P0=NixieTable[Number];
	//这个函数页需要提前定义
	Delay(1);
	//P0和P2是自定义的变量，所以需要先声明，此处就是引入头文件就可以了
	P0=0x00;
}