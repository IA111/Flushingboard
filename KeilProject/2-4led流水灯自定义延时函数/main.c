#include <REGX52.H>
#include <intrins.h>

void Delay1ms(unsigned int xms)		//@12.000MHz
{
	unsigned char i, j;
  while(xms!=0)
	{
		//�⼸�����Դ�����ʱ����
		i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
	 xms=xms-1;//��һ����WHILEѭ��������������һ���Զ�����ʱ
	}
	
}

void main()
{
 while(1)
 {
  P2=0XFE;//??????? 1111 1110
  Delay1ms(100);
	P2=0XFD;//??????? 1111 1101
	Delay1ms(100);
	P2=0XFB;//??????? 1111 1011
	Delay1ms(100);
	P2=0XF7;//??????? 1111 0111
	Delay1ms(100);
	P2=0XEF;//??????? 1110 1111
	Delay1ms(100);
	P2=0XDF;//??????? 1101 1110
	Delay1ms(100);
	P2=0XBF;//??????? 1011 1110
	Delay1ms(100);
	P2=0X7F;//??????? 0111 1110
	Delay1ms(100);
}
}