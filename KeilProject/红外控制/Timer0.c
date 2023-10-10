#include <REGX52.H>

//配置寄存器
void Timer0_Init()
{
	
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0;		//设置定时初值
	TH0 =0;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 0;		//定时器0不计时

}
//设置计数器，把十六位的值放在计数器里面
void Timer0_SetCounter(unsigned int Value)
{
  TH0=Value/256;
	TL0=Value%256;
}
//返回一个16位的数据，虽然这是一个十六位的数据
//但是通过一个Int型数据来接受，就可以直接得到一个整形数据了

unsigned int Timer0_GetCounter(void)
{
return (TH0<<8)|TL0;
}

//决定计时器是不是开始计时
void Timer0_Run(unsigned char Flag)
{
	TR0=Flag;  //在调用哪一个函数给1的时候开始计时，
	//给0的时候上面的配置寄存器那个函数就会停止计时。
	
}