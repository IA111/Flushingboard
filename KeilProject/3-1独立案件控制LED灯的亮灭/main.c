#include <REGX52.H>

void main()
{
		//P2=0xFE;此时操作的是八位也就是八个灯的
	//只操作其中一个的关系如下,头文件也要由reg改称regx
	P2_0=0;
	P2_1=1;
	//一直按，一直可以亮
	while(1)
	{
		//P3表示的是独立案案按键这一块的，
		//P3_1表示按下了第一个独立按键，按下实狭恋浦
	  if(P3_1==0 || P3_2==0)
		{
		  P2_0=0;
		}else{
		  P2_0=1;
		}
	}
}