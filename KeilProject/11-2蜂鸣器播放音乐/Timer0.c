#include <REGX52.H>

//配置寄存器
void Timer0Init()
{
	//配置电路
  //配置TMOD的工作模式,八位也一起赋值，高4位不用管
	//TMOD = 0X01 ;//0000 0001  等价于下面两句
	//TMOD=TMOD&0xF0;  //把TMOD的低四位清0，高四位保持不变
	//TMOD=TMOD|0x01; //把TMOD的最低位置1，高四位保持不变
  //配置Tcon
	//TF0=0;
  //TR0=1;	
	//TH0=64535/256;
	//TL0=64535%256;
	//自动生成
	//AUXR &= 0x7F;		这一句不需要，定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
/*
	这后面几句是配置的中断
	*/
	ET0=1;
	EA=1;
	PT0=0;
}
//定时器中断函数模板,每次使用要议案加到主函数中
//,程序会自动跳转到中断函数处
//即使没有定义，1毫秒中断一次
/*
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TH0=0xFC;
	TL0=0x18;//设置定时初值
	T0Count++;
  if(T0Count>=1000)
	{
	  //重新赋初值
		T0Count=0;
		P2_0=~P2_0;//让P2_0每隔一秒闪烁一次
	}
}
*/