#include <REGX52.H>
/**
  * @brief  串口初始化，波特率设置的是4800
  * @param 
  * @param    
  * @retval Byte 表示串口每一次发送的数据
  */
void UART_Init()
{
  SCON = 0x40;
	PCON |=0x80;
	//选择波特率
	TMOD &=0x0F;
	TMOD |=0x20;//设置定时器模式
	TL1=0xF3;
	TH1=0xF3;
	ET1=0;
	TR1=1;
	/*使用STC软件自动生成
	void UartInit(void)		//4800bps@12.000MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xF3;		//设定定时初值
	TH1 = 0xF3;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}*/
}
//发送数据
void UART_SendByte(unsigned char Byte)
{
   SBUF=Byte;//将字符写入SBUF寄存器之后，只要波特率配置好之后
	           //就会自动发送
	 while(TI==0);//发送完成的标志位
	 TI=0;
}
