#include <REGX52.H>
//#include <>
void Delay1ms(unsigned int xms)		//@12.000MHz
{
	unsigned char i, j;
  //自己定义了参数来控制延时事时间
	while(xms)
	{
	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
	xms--;//自己写的，别的都是生成的
   }
}
//
void main()
{
		while(1)
		{
		 //开始按键判断
			if(P3_1==0)
			{
				//不加延时，在按按键时，会导致没有松开按键灯的状态就已经改变了
			 Delay1ms(20);//由于按键时会单片机内部会抖动
				//所以设置一个延时来跳过这个抖动的时间
				while(P3_1==0)
				{
				 
				}
				//松开按键时也会抖动，也需要延时
				Delay1ms(20);
				//取反,实现按一次灯的状态改变一次
				P2_0=~P2_0;
			}
		}
}
