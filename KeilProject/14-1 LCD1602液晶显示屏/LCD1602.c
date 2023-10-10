#include <REGX52.H>

sbit LCD_RS=P2^6;
sbit LCD_EN=P2^7;
sbit LCD_WR=P2^5;
# define LCD_DataPort P0

void LCD_Delay()		//@12.000MHz
{
	unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}

void LCD_WriteCommand(unsigned char Command)
{
  LCD_RS=0;
	LCD_WR=0;
	LCD_DataPort=Command;
	LCD_EN=1;
	LCD_Delay();//加一个一毫秒的延时，防止他反应不过来
	LCD_EN=0;
	LCD_Delay();
	
}

void LCD_WriteData(unsigned char Data)
{
   LCD_RS=1;
	LCD_WR=0;
	LCD_DataPort=Data;
	LCD_EN=1;
	LCD_Delay();//加一个一毫秒的延时，防止他反应不过来
	LCD_EN=0;
	LCD_Delay();
}
//设置光标位置
void LCD_SetCursor(unsigned char Line,unsigned char Column)
{
 if(Line==1)
 { 
  Column=Column-1;
	LCD_WriteCommand(0x80|(Column)); 
 }
else
 { 
	LCD_WriteCommand(0x80|(Column-1)+0x40); 
 }
}



void LCD_Init()
{
 LCD_WriteCommand(0x38);
 LCD_WriteCommand(0x0C);
 LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x01);
}
void LCD_ShowChar(unsigned char Line,unsigned char Column,unsigned char Char)
{
 if(Line==1)
 { 
  Column=Column-1;
	LCD_WriteCommand(0x80|(Column)); 
 }
else
 { 
	LCD_WriteCommand(0x80|(Column-1)+0x40); 
 }
 LCD_WriteData(Char);
}
void LCD_ShowString(unsigned char Line,unsigned char Column,unsigned char *String)
// *String 以为字符串有很多的字符，所以使用数组来承担，所以传递一个数组的首地址
{
	unsigned char i;
	//设置光标位置
  LCD_SetCursor(Line,Column);
 for(i=0;String[i]!='\0';i++)
 {
  LCD_WriteData(String[i]);
 }

}
//次方函数  x的y次方
int LCD_Pow(int x,int y)
{
unsigned char i;
	int result=1;
	for(i=0;i<y;i++)
	{
	 result=result*x;
	}
	return result;
}

void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned int Length)
{
	//Length 表示传入数的长度
	unsigned char i;
 LCD_SetCursor(Line,Column);
 for(i=Length;i>0;i--)
	{
		//运算的到的数字需要转换成ASCII码
		LCD_WriteData('0'+Number/LCD_Pow(10,i-1)%10);
	}
	 
}
//显示有符号的数字
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned int Length)
{
		unsigned char i;
	unsigned int Number1;//防止取反之后个别数字不可以显示出来
		LCD_SetCursor(Line,Column);
	  if(Number>=0)
		{
		 LCD_WriteData('+');
		 Number1=Number;
		}else{
		 LCD_WriteData('-');
			Number1=-Number;
		}
		for(i=Length;i>0;i--)
	{
		//运算的到的数字需要转换成ASCII码
		LCD_WriteData('0'+Number1/LCD_Pow(10,i-1)%10);
	}
}
//显示十六进制的数字
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
 unsigned char i;
	unsigned int SingleNumber;//P偏移量
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		SingleNumber=Number/LCD_Pow(16,i-1)%16;
		if(SingleNumber<10)
		{
		 LCD_WriteData('0'+SingleNumber);
		}else{
		 LCD_WriteData('A'+SingleNumber-10);
		}
		
	}
}
/**
  * @brief  在LCD1602指定位置开始以二进制显示所给数字
  * @param  Line 起始行位置，范围：1~2
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~1111 1111 1111 1111
  * @param  Length 要显示数字的长度，范围：1~16
  * @retval 无
  */
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData('0'+Number/LCD_Pow(2,i-1)%2);
	}
}
