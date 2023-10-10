#ifndef _DELAY_H
#define _DELAY_H
#include "stm32f10x.h"
void delay_US(u32 time);
void delay_MS(u32 time);

void Delay_Init(void);
void DelayMs(u32 time);
void DelayUs(u32 time);

#endif

