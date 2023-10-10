#ifndef _KEY_H
#define _KEY_H
#include "stm32f10x.h"

u8 Key_Scan(u8 mode);
u8 key_one(void);
u8 key_two(void);
u8 key_three(void);
u8 key_up(void);

#define KEY1   (!!(GPIOE->IDR & 0x0010))
#define KEY2   (!!(GPIOE->IDR & 0x0008))
#define KEY3   (!!(GPIOE->IDR & 0x0004))
#define KEY_UP (!!(GPIOA->IDR & 0x0001))

void Key_Init(void);
#endif


