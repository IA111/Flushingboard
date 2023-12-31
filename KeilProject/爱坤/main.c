#include <REGX52.H>
#include "Delay.h"
#include "MatrixLED.h"

//????
unsigned char code Animation[]={
	0x0C,0xD3,0xFC,0xD2,0x09,0x18,0x18,0x00,
	0x00,0x0C,0x0C,0x09,0xD2,0xFC,0xD3,0x0C,
	0x00,0x38,0x38,0x09,0xD2,0xFC,0xD3,0x0C,
	0x0C,0xD3,0xFC,0xD2,0x21,0xC0,0xC0,0x00,
	0x00,0x05,0x0A,0xD7,0xFB,0xDC,0x03,0x00,
	0x00,0x38,0x38,0x09,0xD2,0xFC,0xD3,0x0C,
	0x00,0x0B,0xDC,0xFB,0xD7,0x0A,0x05,0x00,
	0x00,0x20,0x7F,0xF8,0xB4,0x02,0x01,0x01,
	0x00,0x00,0x19,0x3F,0x7C,0x57,0x01,0x00,
	0x00,0x00,0x01,0x02,0x1C,0x3C,0x7B,0x58,
	0x00,0x00,0x19,0x3F,0x7C,0x57,0x01,0x00,
	0x00,0x00,0x19,0x3F,0x7C,0x57,0x01,0x00,
	0x20,0x10,0x20,0xFF,0xFC,0x26,0x12,0x08,
	0x00,0xC0,0x20,0xFF,0xFA,0x24,0xC0,0x00,
	0x00,0x00,0x30,0x7F,0xFE,0xA2,0x01,0x00,
    0x00,0x07,0x34,0x78,0xF8,0xB6,0x01,0x00,
	0x00,0x00,0x01,0x02,0x1C,0x3C,0x7B,0x58,
	0x00,0x07,0x34,0x78,0xF8,0xB6,0x01,0x00,
	0x00,0x00,0x01,0x02,0x1C,0x3C,0x7B,0x58,
	0x00,0x07,0x34,0x78,0xF8,0xB6,0x01,0x00,
	0x00,0x00,0x01,0x02,0x1C,0x3C,0x7B,0x58,
	};

void main()
{
	unsigned char i,Offset=0,Count=0;
	MatrixLED_Init();
	while(1)
	{
		for(i=0;i<8;i++)	
		{
			MatrixLED_ShowColumn(i,Animation[i+Offset]);
		}
		Count++;			
		if(Count>30)
		{
			Count=0;
			Offset+=8;		
			if(Offset>160)
			{
				Offset=0;
			}
		}
	}
}
