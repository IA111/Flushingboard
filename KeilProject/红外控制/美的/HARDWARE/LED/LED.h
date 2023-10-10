#ifndef _LED_H
#define _LED_H
#include "stm32f10x.h"
#include "sys.h"
/*
函数功能：LED初始化；
硬件连接：
		LED1 -> PF7;
		LED2 -> PB5;
		LED3 -> PA8;
		LED4 -> PA1;
*/
void Led_Init(void);
void Beep_Init(void);
//#define LED1(x) if(x){GPIOF->ODR |=1<<7;}else{GPIOF->ODR &=~(1<<7);}
//#define LED2(x) if(x){GPIOB->ODR |=1<<5;}else{GPIOB->ODR &=~(1<<5);}
//#define LED3(x) if(x){GPIOA->ODR |=1<<8;}else{GPIOA->ODR &=~(1<<8);}
//#define LED4(x) if(x){GPIOA->ODR |=1<<1;}else{GPIOA->ODR &=~(1<<1);}
//#define BEEP(x) if(x){GPIOB->ODR |=1<<8;}else{GPIOB->ODR &=~(1<<8);}

#define LED1 PFout(7)
#define LED2 PBout(5)
#define LED3 PAout(8)
#define LED4 PAout(1)

#define BEEP PBout(8)

#endif

