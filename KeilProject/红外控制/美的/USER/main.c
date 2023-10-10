#include "led.h"
#include "key.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "exti.h"
#include "time.h"
int main(void)
{
//	u8 dat0[6]={77,178,249,6,11,244};
//	u8 dat1[6]={77,178,249,6,11,244};
	u8 KEY;
	Key_Init();
	Led_Init();
	Delay_Init();
	Usart1_Init(115200);	
	Time6_Init(72,65535);
	while(1)
	{
		KEY=Key_Scan(0);
		if(KEY==2)
		{
			u8 dat0[6]={77,178,248,7,27,228};//kai
			u8 dat1[6]={77,178,248,7,27,228};
			Send38KHz(1,4323);
			Send38KHz(0,4520);
			
			MD_Code(dat0);
			Send38KHz(1,425);
			IE=0;
			DelayUs(5336);
			Send38KHz(1,4323);
			Send38KHz(0,4520);
			MD_Code(dat1);
			Send38KHz(1,560);
			Send38KHz(0,560);
		}
		if(KEY==4)
		{
			u8 dat0[6]={77,178,222,33,7,248};
			u8 dat1[6]={77,178,222,33,7,248};
			Send38KHz(1,4323);
			Send38KHz(0,4520);
			
			MD_Code(dat0);
			Send38KHz(1,425);
			IE=0;
			DelayUs(5336);
			Send38KHz(1,4323);
			Send38KHz(0,4520);
			MD_Code(dat1);
			Send38KHz(1,560);
			Send38KHz(0,560);
		}
		
		
		
		  if(IR==0)  //等待红外线信号
			{
				 if(GetInfrad()==0)  //解码成功
				 {
					 printf(" %d  %d  %d  %d  %d  %d\r\n",IR_data[0],IR_data[1],IR_data[2],IR_data[3],IR_data[4],IR_data[5]);

				 }
			}
	}
}
