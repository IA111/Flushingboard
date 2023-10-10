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
函数功能：获取高电平持续的时间
*/
u32 GetTimeH(void);
/*
函数功能：获取低电平持续的时间
*/
u32 GetTimL(void);
/*
函数功能：NEC红外协议解码
返回值：返回0成功，其他值失败
*/
u8 GetInfrad(void);

void Send38KHz(u8 flag,u32 time);
void NEC_Code(u8 user_dat,u8 key_dat);
void MD_Code(u8 dat[]);



#endif
