#include <REGX52.H>
sbit IRIN=P3^2;
void Int0_Init(void)
{
  IT0=1;//下降沿触发

	EX0=1;
	EA=1;
	PX0=1;
	IRIN=1;
}
/*
void Int0_Routine(void) interrupt 0
{
  
}
*/