#include <REGX52.H>
#include "Delay1.h"
#include "MatrixLED.h"
//自己设置一个字符，在使用取模软件自动生成
unsigned char Animation[]={
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0xFF,0x18,0x08,0x18,0xFF,0x00,0x00,0xFF,0x91,0x91,0x00,0x00,0xFF,0x01,0x01,0x00,
0xFF,0x01,0x01,0x00,0x7E,0x81,0x81,0x81,0x81,0x7E,0x00,0x00,0x00,0xF9,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	
};
void main()
{
	unsigned char i;
	unsigned char Offset=0,count=0;
  MatrixLED_Init();
/*
  MatrixLED_ShowColumn(0,0xAA);
  亮点阵屏的第0列的 10101010 为1的亮
	*/
	/*
	由于这个开发板没有LED灯，直接设置LED显示屏幕，
	然后需要拔掉他旁边的J24跳线帽
	*/
  
	while(1)
	{ 
		for(i=0;i<8;i++)
		{
		MatrixLED_ShowColumn(i,Animation[i+Offset]);
		}
		count++;
		//扫描次数
		if(count>10)
		{
		 count=0;
		Offset++;
			if(Offset>40)
			{
			Offset=0;
			}
		}
		//可以自己构建图形，一列一列的来
		/*亮灯的表示1.不亮的就是0，别的
	  	MatrixLED_ShowColumn(0,Animation[0]);
      MatrixLED_ShowColumn(1,Animation[1]);
			MatrixLED_ShowColumn(2,Animation[2]);
     	MatrixLED_ShowColumn(3,Animation[3]);
		  MatrixLED_ShowColumn(4,Animation[4]);
     	MatrixLED_ShowColumn(5,Animation[5]);
	    MatrixLED_ShowColumn(6,Animation[6]);
   	  MatrixLED_ShowColumn(7,Animation[7]);
*/
	}
}