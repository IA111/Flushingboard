#include <REGX52.H>
unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
void Nixie(unsigned int Location,unsigned char Number)
{
	switch(Location)
	{
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

void Delay(unsigned int Nienum)		//@12.000MHz
{
	unsigned char i, j;
  while(Nienum)
	{
	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
	Nienum--;
  }
}

void main()
{
	/*
	  原理：当延时很短的时候，这个数码管显示就会一起出现不会闪了，不过此时
	  还是一个一个依次亮的
	*/
	while(1)
	{
		Nixie(1,1);
		Delay(1);
		Nixie(2,2);
		Delay(1);
		Nixie(3,3);
		Delay(1);
	}
}
