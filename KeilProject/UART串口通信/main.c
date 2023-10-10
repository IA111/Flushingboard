#include <REGX52.H>
#include "LCD1602.h"
#include "UART.h"
unsigned char temp;
void main()
{
	LCD_Init();
	UART_Init(4800);
	EA=1;//打开所有中断
    while(1)
  {
    LCD_ShowHexNum(1,1,temp,2);
   }
}

//串口中断的中断号是4
void UART_Zhongduan() interrupt 4
{
	/*
	注意两个引脚RI以及TI
	RI:当数据在从单总线到接受控制器的的时候，作为标志位，
	TI：是数据在从单总线进行发送的时候，作为发送是不是已经完成的标志位
	
	*/
  if(RI==1)
	{
	  RI=0;
		temp=SBUF;
	}
	
}