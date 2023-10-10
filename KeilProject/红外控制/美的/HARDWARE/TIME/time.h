#ifndef _TIMER_H
#define _TIMER_H

#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"

void Time6_Init(u32 Psc,u32 Arr);

#define IR PBin(9)
#define IE PEout(6)
extern u8 IR_data[6];

/*
�������ܣ���ȡ�ߵ�ƽ������ʱ��
*/
u32 GetTimeH(void);
/*
�������ܣ���ȡ�͵�ƽ������ʱ��
*/
u32 GetTimL(void);
/*
�������ܣ�NEC����Э�����
����ֵ������0�ɹ�������ֵʧ��
*/
u8 GetInfrad(void);

void Send38KHz(u8 flag,u32 time);
void NEC_Code(u8 user_dat,u8 key_dat);
void MD_Code(u8 dat[]);



#endif
