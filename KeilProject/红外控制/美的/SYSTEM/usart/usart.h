#ifndef _USART_H
#define _USART_H

#include "stm32f10x.h"
#include "stdio.h"

void Usart1_Init(u32 bound);
void Usart_SendStr(USART_TypeDef *Usartx,u8 *str );

//ÕûÊý×ª×Ö·û´®
void Usart_Send_integer(USART_TypeDef *Usartx,u32 data);

void Usart_Send_binary(USART_TypeDef *Usartx,u8 data);


extern u8 Buffer[100];
extern u8 RXcount;
extern u8 Revflag;

#endif
