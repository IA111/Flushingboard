#include <REGX52.H>
#include "Delay1.h"
#include "Key.h"
#include "Nixie.h"
#include "Buzzer.h"

 
 
unsigned char KeyNum;//定义被按的按键值

void main()
{
	Nixie(1,0);
  while(1)
	{
	  KeyNum=Key();
		if(KeyNum)
		{
			Buzzer_time(100);
			Nixie(1,KeyNum);
		}
	}
}