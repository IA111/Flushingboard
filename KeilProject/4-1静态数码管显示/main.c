#include <REGX52.H>
unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
//��һ��������ʾλ�ã��ڶ���������ʾʲô����
void Nixie(unsigned int Location,unsigned char Number)
{
	switch(Location)
	{
		//��Ϊ��һ��������ʾ�����������������Y7��������Ϊ111�������������˿�Ϊ111
	  case 1:P2_4=1;P2_3=1;P2_2=1; break;
	  case 2:P2_4=1;P2_3=1;P2_2=0; break;
		case 3:P2_4=1;P2_3=0;P2_2=1; break;
		case 4:P2_4=1;P2_3=0;P2_2=0; break;
		case 5:P2_4=0;P2_3=1;P2_2=1; break;
		case 6:P2_4=0;P2_3=1;P2_2=0; break;
		case 7:P2_4=0;P2_3=0;P2_2=1; break;
		case 8:P2_4=0;P2_3=0;P2_2=0; break;
	}
	P0=NixieTable[Number];
}

void main()
{
	Nixie(7,0);
	while(1){}
	//����˼·
	//Ϊ�����������ʾ������Ϊ��74LS138��������
	//LED6�����Y5��101����������ֵ
	//P2_4=1;
	//P2_3=0;
	//P2_2=1;
	/*
	0111 1101 ��������ܵ�dpABCDEFG,������Ա�֤�������ʾ6
	ͨ��74HC245 ��������P0����ֱ�Ӷ�Ӧ��ȥ�����ÿһλ����P07��ʼ��Ӧ
	�Ӹ�λ����λ

	P0=0x7D;
   while(1)
	 {
	   
	 }
	*/
}
