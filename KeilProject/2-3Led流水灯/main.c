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
	//����һ����һ����ˮ��ʵ�ַ�ʽ
 while(1)
{
  P2=0XFE;//������ˮ��ԭ�� 1111 1110
	Delay500ms();
	P2=0XFD;//������ˮ��ԭ�� 1111 1101
	Delay500ms();
	P2=0XFB;//������ˮ��ԭ�� 1111 1011
	Delay500ms();
	P2=0XF7;//������ˮ��ԭ�� 1111 0111
	Delay500ms();
	P2=0XEF;//������ˮ��ԭ�� 1110 1111
	Delay500ms();
	P2=0XDF;//������ˮ��ԭ�� 1101 1110
	Delay500ms();
	P2=0XBF;//������ˮ��ԭ�� 1011 1110
	Delay500ms();
	P2=0X7F;//������ˮ��ԭ�� 0111 1110
	Delay500ms();
}
}