#include <REGX52.H>


//传入参数，波特率
void UART_Init(unsigned int ptr)
{
  TMOD=(TMOD&0X0F)|0X20;
	TH1=256-11059200/32/12/ptr;//TH1的计算方式
	TL1=TH1;
	TR1=1;//定时器1开始工作
	ET1=0;
	SCON=0X50;
	ES=1;
}
//发送数据
void UART_SendData(unsigned char inf)
{
  SBUF=inf;//数据缓冲寄存器,只要把这个数据放入SBUF中，他就会自动发出去
	while(TI==0);
	//数据发送结束之后，TI表示标志位，会自动置1，同时结束循环，从新
	//把TI置0，以便于下一次的发送
	TI=0;
	
}
