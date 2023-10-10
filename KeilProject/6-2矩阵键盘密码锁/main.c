#include <REGX52.H>
#include "Delay1.h"
#include "LCD1602.h"
#include "MatrixKey.h"


/*
实现从新设置密码功能以及计次清零,取消是回位而不是直接全部删除
*/



unsigned char KeyNum;
unsigned int Password;
unsigned int count;
void main()  
{
	 LCD_Init();
	LCD_ShowString(1,1,"Password:");//	第一个参数是起始行位置，第二个参数是起始列位置
   while(1)
	 {
	  KeyNum=MatrixKey();
		if(KeyNum)
		{
			//s1-s10按键按下，就是在输入密码
			if(KeyNum<=10)
			{
				//因为输密码是从前往后，就相当于先输入高位数字，所以要乘以10，
			   if(count<4)
				 {
				 Password*=10;
				 Password +=KeyNum%10;
				 count++;//记录密码位数
				 }
				
				//Password *=10;
				//Password += KeyNum%10;//按谁表示就是几号，取余是因为10号按键表示0
			}			
			LCD_ShowNum(2,1,Password,4);//在LED屏幕上显示第几个按键
		}
		if(KeyNum==11)//如果11按键按下，表示密码确认，
		{
			//如果初始密码不为2345则这个就会出错
		  if(Password==2345)
			{
			  LCD_ShowString(1,13,"OK ");
				Password=0;
        count=0;//可以实现从新输入
				//LCD_ShowString(1,14,"  ");
        LCD_ShowNum(2,1,Password,4);				
			}else{
			 LCD_ShowString(1,13,"ERR");
				Password=0;
				count=0;//
				//LCD_ShowString(1,13,"   ");
				LCD_ShowNum(2,1,Password,4);//更新显示，显示删除之后的
			}
		}
		if(KeyNum==12)//K12被设置成了取消键
		{
			Password=0;
			count=0;
			LCD_ShowNum(2,1,Password,4);
		}
	}	
 }
