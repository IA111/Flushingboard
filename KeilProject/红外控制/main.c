#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "Int0.h"
#include "Timer0.h"
#include "IR.h"

unsigned char Num;
unsigned int Time;//计时时间

unsigned char Address;
unsigned char Command;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"A");
  IR_Init();
    while(1)
  {
   if(IR_GetDataFlag())
	 {
	  Address=IR_GetAddress();
		Command=IR_GetCommand();
		 LCD_ShowHexNum(2,1,Address,2);
		 LCD_ShowHexNum(2,5,Command,2);
	 }
   }
}

	