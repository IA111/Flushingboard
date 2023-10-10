#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
unsigned char A=0xB2;
unsigned char B=0x7b;
unsigned char C=0xe0;





void signal(char num)
	{
   switch(num)
	 {
	   case 'L':
			 TIM_SetCompare2(TIM3,1895/3);
	    delay_us(4400 );
	    TIM_SetCompare2(TIM3,0);
	     delay_us(4400);
	     break;
		 
 		   case '1':
					 TIM_SetCompare2(TIM3,1895/3); 
	    delay_us(540);
	    TIM_SetCompare2(TIM3,0);
	     delay_us(1620);
			 break;
			 
			   case '0':
			 	 TIM_SetCompare2(TIM3,1895/3); 
	    delay_us(540);
	     TIM_SetCompare2(TIM3,0); 
	     delay_us(540);
				 break;				 
				case 'S':
			 TIM_SetCompare2(TIM3,1895/3);  
	    delay_us(540);
	    TIM_SetCompare2(TIM3,0); 
	     delay_us(5220);
       break;	

      case 'R':
			TIM_SetCompare2(TIM3,1895/3);
	    delay_us(540);
	      TIM_SetCompare2(TIM3,0); 
	     delay_us(20000);
       break;					 
				 default:break;
	 } 
}

void panduan(unsigned char num)
{
  unsigned char mask; 
	//signal('L');
	
	
  for(mask=0x80;mask!=0;mask>>=1)
	{ 
      if(mask & num)
         signal('1');
      else 
         signal('0');
  }
	
	  for(mask=0x80;mask!=0;mask>>=1)
	{
			
			if(mask & (~num))
         signal('1');
      else 
         signal('0');
  }

}

 int main(void)
 {		



	 delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 //串口初始化为9600
 	LED_Init();			     //LED端口初始化
 	TIM3_PWM_Init(1895,0);	 //不分频。PWM频率=72000/900=8Khz
				
	while(1)
	{
		 signal('L');
		 panduan(A);
		 panduan(B);
		 panduan(C);
		 signal('S'); 
		 signal('L');
		 panduan(A);
		 panduan(B);
		 panduan(C);
		 signal('R');
		delay_ms(110);
	}

}

 
