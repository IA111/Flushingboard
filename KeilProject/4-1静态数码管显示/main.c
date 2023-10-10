#include <REGX52.H>
unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
//第一个参数显示位置，第二个参数显示什么数字
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
}

void main()
{
	Nixie(7,0);
	while(1){}
	//整体思路
	//为了让数码管显示六，因为在74LS138译码器上
	//LED6结的是Y5，101，所以设置值
	//P2_4=1;
	//P2_3=0;
	//P2_2=1;
	/*
	0111 1101 ，在数码管的dpABCDEFG,这个可以保证数码管显示6
	通过74HC245 ，来设置P0就是直接对应上去输出的每一位，从P07开始对应
	从高位到低位

	P0=0x7D;
   while(1)
	 {
	   
	 }
	*/
}
