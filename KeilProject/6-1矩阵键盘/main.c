#include <REGX52.H>
#include "Delay1.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char KeyNum;

void main()  
{
	 LCD_Init();
	 LCD_ShowString(1,5,"hello world");//	第一个参数是起始行位置，第二个参数是起始列位置
   while(1)
	 {
	    KeyNum=MatrixKey();
		if(KeyNum!=0)
		{
			LCD_ShowNum(2,1,KeyNum,2);//在LED屏幕上显示第几个按键
		}
	 }
}