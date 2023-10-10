#include <REGX52.H>
#include "Delay1.h"
/**
  * @brief  获取独立按键编码
  * @param  无
  * @param   无 
  * @retval 有一个返回值，返回每一次按键的编号
	无按键按下时，返回值为0
  */

unsigned char Key()
{
  unsigned char KeyNumber=0;
	/*按键检测*/
	if(P3_1==0){Delay1(20);while(P3_1==0);Delay1(20);KeyNumber=1;}
	if(P3_0==0){Delay1(20);while(P3_0==0);Delay1(20);KeyNumber=2;}
	if(P3_2==0){Delay1(20);while(P3_2==0);Delay1(20);KeyNumber=3;}
	if(P3_3==0){Delay1(20);while(P3_3==0);Delay1(20);KeyNumber=4;}
	return KeyNumber;
}