#include <REGX52.H>

void Delay(unsigned int xms)
{
 unsigned char i,j;
	while(xms)6
	{
	  i=2;
		j=239;
		do{
		 while(--j);
		}while(--i);
		xms--;
	}
}
unsigned char LedNum=0;
void main()
{
	
	  P2=0xFE;
  while(1)
	{
		//��ʾ����������������һ��
	  if(P3_1==0)
		{
			//ȥ�������Ķ���
		  Delay(20);
			while(P3_1==0)
			Delay(20);
			
			LedNum=LedNum+1;//
      if(LedNum>=8)
			{
			   LedNum=0;//���LedNum�ӵ��ڰ�λ�ˣ��͹��㣬��Ϊ��λ�����ܴ���8
			   
			}
			P2=~(0x01<<LedNum);
         //����һ��
		}			
			if(P3_0==0)
			{
			  Delay(20);
			  while(P3_0==0)
			  Delay(20);
				if(LedNum==0)
				{LedNum=7;}
				else
				{LedNum--;}
				P2=~(0x01<<LedNum);
			}				
		
	}
}