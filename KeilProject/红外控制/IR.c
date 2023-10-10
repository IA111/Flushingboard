#include <REGX52.H>
#include "Timer0.h"
#include "Int0.h"
sbit IRIN=P3^2;
unsigned int IR_Time;  //计时
unsigned char IR_State; //定义状态

unsigned char IR_Data[4];//表示四个字节
unsigned char IR_pData;//用于记录是不是把32位数据全部收到，标志

unsigned char IR_DataFlag;//就就是如果数据如果收到了，就置1。用于在主函数中进行判断
unsigned char IR_RepeatFlag;//重发标志位

unsigned char IR_Address;//存最终的结果
unsigned char IR_Command;//命令码

void IR_Init(void)
{
  Timer0_Init();//定时器初始化
  Int0_Init();// 中断初始化
 
}
unsigned char IR_GetDataFlag(void)
{
 if(IR_DataFlag)
 {
  IR_DataFlag=0;
	 return 1;
 }
 return 0;
}
unsigned char IR_GetRepeatFlag(void)
{
 if(IR_RepeatFlag)
 {
  IR_RepeatFlag=0;
  return 1;
 }
 return 0;
}


unsigned char IR_GetAddress(void)
{
 return IR_Address;
}

unsigned char IR_GetCommand(void)
{
 return IR_Command;
}
void Int0_Routine(void) interrupt 0
{
   //因为最开始这个状态时空闲状态，定义为0,表示此时空闲
	if((IR_State==0)&&(IRIN==1))
	{
	  Timer0_SetCounter(0);//确保这个计数器从0开始
		Timer0_Run(1);//参数1表示计数器开始计数
		IR_State=1;
	}
	//此时就是当上一次进中断之后，这个状态被设置了
	//然后下一次进中断，因为这个IR_sTATE==1,所以可以直接进行数其中的间隔时间就可以了
	
	else if(IR_State==1)
	{
    IR_Time=Timer0_GetCounter();//读到从高电平到低电平，又是高电平的时间间隔
		Timer0_SetCounter(0);//清0.方便下一次计时
	   /*
		  根据NEC编码可以得到，这个Start标志的时间，以及repeat标志的时间
		以此来进行判断这个是什么
		*/
		//为什么是一个范围，因为这个按键可能有抖动，所以时间不可能是刚好13500微秒
		if(IR_Time>13500-500 && IR_Time<13500+500)
		{
			
		  IR_State=2;//表示下一次再来中断就要开始解码数据部分了
		}else if(IR_Time>11250-500 && IR_Time<11250+500)
		{
			//接受到这个信号表示这一帧已经结束了，后面已经不会使用数据了
			IR_RepeatFlag=1;
			//停止计时器
			Timer0_Run(0);
			IR_State=0;//从新把这个状态置位0
		}
		else
		{
		  //解码错误才会出现
			IR_State=1;
		}
	}
	//开始解码
	else if(IR_State==2)
	{
	IR_Time=Timer0_GetCounter();
	Timer0_SetCounter(0);
		//这是逻辑0的
	 if(IR_Time>1120-500 && IR_Time<1120+500)
	  {
		  /*
		  每一次都是四个字节的数据，以此存取32位
		  */
	     IR_Data[IR_pData/8] &= ~(0x01<<(IR_pData%8));
		  IR_pData++;
	  }
	  	//这是逻辑1的
	 else if(IR_Time>2250-500 && IR_Time<2250+500)
	  {
		  /*
		  每一次都是四个字节的数据，以此存取32位
		  */
	     IR_Data[IR_pData/8] &= ~(0x01<<(IR_pData%8));
		  IR_pData++;
	  }
	  else{
	  IR_pData=0;
	  IR_State=1;
	  }
	  //因为这是表示计算数据位数的，且这个数据是32位，所以判断是不是收结束了
	  if(IR_pData>=32)
	  {
	   IR_pData=0;
		  //根据器NEC编码得到的
		   if((IR_Data[0]==~IR_Data[1]) && (IR_Data[2]==~IR_Data[3]) )
		   {
			   //上述判断说明数据验证正确
			   //把数据转存过去
			   IR_Address=IR_Data[0];
			   IR_Command=IR_Data[2];
			   IR_DataFlag=1;//告诉他已经收到数据了
		   }
	   Timer0_Run(0);
	   IR_State=0;
	  }
	}
}