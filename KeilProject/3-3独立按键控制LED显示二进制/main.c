#include <REGX52.H>

void Delay(unsigned int xms)		//@12.000MHz
{
	unsigned char i, j;
 while(xms)
 {
	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
	xms=xms-1;
  }
}

void main()
{
	unsigned char LED_num=0;
	while(1)
	{
		//P2_0=0;
	 if(P3_1==0)
	 {
			//���ǽ��а����������Ҫ�Ĳ���
		  Delay(20);
			//������û������
			while(P3_1==0);
			Delay(20);
			//��ʱP2�ı�ʾ�����еĵƵ�״̬ 1111 1111 ȫ����
		 //��ʦ����ģ���ʱ���Ʊ�ʾ1��������ʾ����0
			LED_num++;
			P2=~LED_num;
		 //������һ��ʱ�Լ�������ģ�����Ƶ�����ʾ0�����ʾ1
		// P2=P2+0x01;
		}
	}
}