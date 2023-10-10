#include <REGX52.H>
#include "Delay.h"

sbit RCK=P3^5;		//RCLK
sbit SCK=P3^6;		//SRCLK
sbit SER=P3^4;		//SER

#define MATRIX_LED_PORT		P0

/**
  * @brief  74HC595??????
  * @param  Byte ??????
  * @retval ?
  */
void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		SER=Byte&(0x80>>i);
		SCK=1;
		SCK=0;
	}
	RCK=1;
	RCK=0;
}

/**
  * @brief  ??????
  * @param  ?
  * @retval ?
  */
void MatrixLED_Init()
{
	SCK=0;
	RCK=0;
}

/**
  * @brief  LED?????????
  * @param  Column ?????,??:0~7,0????
  * @param  Data ????????,????,1??,0??
  * @retval ?
  */
void MatrixLED_ShowColumn(unsigned char Column,Data)
{
	_74HC595_WriteByte(Data);
	MATRIX_LED_PORT=~(0x80>>Column);
	Delay(1);
	MATRIX_LED_PORT=0xFF;
}
