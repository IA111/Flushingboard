#include <REGX52.H>
#include "Delay1.h"
#include "LCD1602.h"
#include "MatrixKey.h"
#include "xiugaimatrix.h"

/*
main.c文件中就是实现教程中的要求
这个xiugai.c文件中实现的是下面的这俩功能：
1.实现重新设置密码功能，通过对比设置的密码和输入的密码
2.输错一个数字的时候，不是全部重新输入，改成了退位。
*/



unsigned char KeyNum,KeyNum1;
unsigned int Passwordset;
unsigned int Password;
unsigned int count,num;
unsigned int aa;//用于判断输入的是多少
void main()  
{
		LCD_Init();
		// LCD_ShowString(2,1,"Password:");//	第一个参数是起始行位置，第二个参数是起始列位置
	while(1)
	{
//	KeyNum1=MatrixKey1();
	KeyNum=MatrixKey();
	if(KeyNum==13)
	{
		LCD_ShowString(1,1,"PasswordSet:");
	}else if(KeyNum)
	{
	if(KeyNum<=10)
	{
		if(num<4)
		{
		Passwordset*=10;
		Passwordset+=KeyNum%10;
		num++;
	  }
    aa++;
		LCD_ShowNum(1,13,Passwordset,4);//显示出第一次设置的密码
	}
}	
  if(KeyNum==14)
   {
		LCD_ShowString(2,1,"Password:");
	 }
		else if(aa>4)
		{
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
					
			LCD_ShowNum(2,10,Password,4);//在LED屏幕上显示第几个按键
			 }
}} 
	if(KeyNum==11)//如果11按键按下，表示密码确认，
		{
			//如果初始密码不为2345则这个就会出错
		  if(Password==Passwordset)
			{
			  LCD_ShowString(2,15,"OK ");
				Password=0;
        count=0;//可以实现从新输入
				//LCD_ShowString(1,14,"  ");
        LCD_ShowNum(2,10,Password,4);				
			}else{
			 LCD_ShowString(2,15,"ER");
				switch(count)
				{
					case 1:Password=Password%Password;break;
					case 2:Password=Password/10;break;
					case 3:Password=Password/10;break;
					default: Password=0;break;
					
				}
				count=0;//
				//LCD_ShowString(1,13,"   ");
				LCD_ShowNum(2,10,Password,4);//更新显示，显示删除之后的
			}
		}

	
}
	}
