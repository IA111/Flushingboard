#include <REGX52.H>

void Delay(unsigned int xms)		//@12.000MHz
{
	unsigned char i, j;
 while(xms)
 {
	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
	xms=xms-1;
  }
}

void main()
{
	unsigned char LED_num=0;
	while(1)
	{
		//P2_0=0;
	 if(P3_1==0)
	 {
			//这是进行按键检测所需要的步骤
		  Delay(20);
			//检验有没有松手
			while(P3_1==0);
			Delay(20);
			//此时P2的表示的所有的灯的状态 1111 1111 全不亮
		 //老师讲解的，此时亮灯表示1，不亮表示的是0
			LED_num++;
			P2=~LED_num;
		 //下面这一步时自己想出来的，这个灯的亮表示0，灭表示1
		// P2=P2+0x01;
		}
	}
}