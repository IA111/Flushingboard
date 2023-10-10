#include <REGX52.H>
#include "Delay1.h"
//RCLK=RCK,系统的等于自己命名的
sbit RCK =P3^5;//进行从新声明，为了更号理解，表示P3的第五位
sbit SCK=P3^6;
sbit SER=P3^4;

void _74HC595_WriteByte(unsigned char Byte)
{
  unsigned int i;
	for(i=0;i<8;i++)
	{
		SER=Byte &(0x80>>i);
		SCK=1;
		SCK=0;
		/*
  SER=Byte &0x80; //如果他的最高为1，则&1000 0000之后最高位为1
  /*
	在写时SER只能等于1或者0，但是这个如果等号右非0时，
	就会自动等于1
	
	SCK=1;//和主函数=0，构成一个上升沿
	SCK=0;//回位
	SER=Byte&0x40;//移第二位
	SCK=1;
	SCK=0;
	SER=Byte&0x20;
	SCK=1;
	SCK=0;
		这样一共要写八次太慢了，使用一个循环*/
	}
	RCK=1;
	RCK=0;
}
/**
  * @brief  点阵屏初始化函数
  * @param 
  * @param    
  * @retval 
  */
void MatrixLED_Init()
{
  SCK=0;
	RCK=0;
}

/**
  * @brief  LED显示屏显示一列数据
  * @param  Column 表示要选择的列，依次0-7
  * @param  Data表示选择一列的行，也就是这一列拿一些灯亮，
            高位在上，1表示亮，0表示灭
  * @retval 
  */
void MatrixLED_ShowColumn(unsigned char Column,unsigned char Data)
{
   _74HC595_WriteByte(Data);
	P0=~(0x80>>Column);//也可以用if()
	//段选 位选 延时 位清零
	Delay1(1);
	P0=0xff;
}