#include <REGX52.H>
#include "Delay1.h"
/**
  * @brief  矩阵键盘读取按键键码
  * @param  无
  * @param    
  * @retval  返回值：KeyNumber 按下按键的键码值，
                  如果按键按键按下不松手，程序会停留在此函数
				  松手的一瞬间，返回键码值，没有按键按下时，返回0.
  */
unsigned char MatrixKey()
{
   unsigned char KeyNumber =0;//局部变量使用要赋初值
  //这个是为了用于区分键盘的每一个编号 
	
	// 扫描第一列的键盘
     P1=0xFF;//此时P1全部置高电平
     P1_3=0;//数字键盘的第一列全部置0
	  //s1按键的检测
     if(P1_7==0)
     {//检测松手的几个基本函数 
		 Delay1(10);while(P1_7==0);Delay1(20);KeyNumber=1;}			
     if(P1_6==0)
     {//检测松手的几个基本函数 
		 Delay1(10);while(P1_6==0);Delay1(20);KeyNumber=5;}			 
	   if(P1_5==0)
     {//检测松手的几个基本函数 
		 Delay1(10);while(P1_5==0);Delay1(20);KeyNumber=9;}	
		 if(P1_4==0)
     {//检测松手的几个基本函数 
		 Delay1(10);while(P1_4==0);Delay1(20);KeyNumber=13;}	
	
		 // 扫描第二列的键盘
     P1=0xFF;//此时P1全部置高电平
     P1_2=0;//数字键盘的第二列全部置0
	  //s1按键的检测
     if(P1_7==0)
     {//检测松手的几个基本函数 
		 Delay1(10);while(P1_7==0);Delay1(20);KeyNumber=2;}			
     if(P1_6==0)
     {//检测松手的几个基本函数 
		 Delay1(10);while(P1_6==0);Delay1(20);KeyNumber=6;}			 
	   if(P1_5==0)
     {//检测松手的几个基本函数 
		 Delay1(10);while(P1_5==0);Delay1(20);KeyNumber=10;}	
		 if(P1_4==0)
     {//检测松手的几个基本函数 
		 Delay1(10);while(P1_4==0);Delay1(20);KeyNumber=14;}	
		 
		 // 扫描第三列的键盘，每一列连接的代号
     P1=0xFF;//此时P1全部置高电平
     P1_1=0;//数字键盘的第三列全部置0
	  //s1按键的检测
     if(P1_7==0)
     {//检测松手的几个基本函数 
		 Delay1(10);while(P1_7==0);Delay1(20);KeyNumber=3;}			
     if(P1_6==0)
     {//检测松手的几个基本函数 
		 Delay1(10);while(P1_6==0);Delay1(20);KeyNumber=7;}			 
	   if(P1_5==0)
     {//检测松手的几个基本函数 
		 Delay1(10);while(P1_5==0);Delay1(20);KeyNumber=11;}	
		 if(P1_4==0)
     {//检测松手的几个基本函数 
		 Delay1(10);while(P1_4==0);Delay1(20);KeyNumber=15;}	
		 
		 // 扫描第一列的键盘
     P1=0xFF;//此时P1全部置高电平
     P1_0=0;//数字键盘的第四列全部置0
	  //s1按键的检测
     if(P1_7==0)
     {//检测松手的几个基本函数 
		 Delay1(10);while(P1_7==0);Delay1(20);KeyNumber=4;}			
     if(P1_6==0)
     {//检测松手的几个基本函数 
		 Delay1(10);while(P1_6==0);Delay1(20);KeyNumber=8;}			 
	   if(P1_5==0)
     {//检测松手的几个基本函数 
		 Delay1(10);while(P1_5==0);Delay1(20);KeyNumber=12;}	
		 if(P1_4==0)
     {//检测松手的几个基本函数 
		 Delay1(10);while(P1_4==0);Delay1(20);KeyNumber=16;}	
		 
		 return KeyNumber;
}