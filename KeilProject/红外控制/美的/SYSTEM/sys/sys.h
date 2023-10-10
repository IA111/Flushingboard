#ifndef SYS_H
#define SYS_H
#include "stm32f10x.h"

#define GPIOA_IDR (0x40010800+0x08)
#define GPIOA_ODR (0x40010800+0x0C)
#define GPIOB_IDR (0X40010C00+0x08)
#define GPIOB_ODR (0X40010C00+0x0C)
#define GPIOC_IDR (0x40011000+0x08)
#define GPIOC_ODR (0x40011000+0x0C)
#define GPIOD_IDR (0x40011400+0x08)
#define GPIOD_ODR (0x40011400+0x0C)
#define GPIOE_IDR (0x40011800+0x08)
#define GPIOE_ODR (0x40011800+0x0C)
#define GPIOF_IDR (0x40011C00+0x08)
#define GPIOF_ODR (0x40011C00+0x0C)
#define GPIOG_IDR (0x40012000+0x08)
#define GPIOG_ODR (0x40012000+0x0C)
	
//把“位带地址＋位序号”转换成别名地址的宏
#define BITBAND(addr,bitnum) ((addr&0xF0000000)+0x2000000+((addr&0xFFFFF)<<5)+(bitnum<<2))

//把该地址转换成一个指针
#define MEM_ADDR(addr) *((volatile unsigned long *) (addr))
	
#define PAout(x) 	MEM_ADDR(BITBAND(GPIOA_ODR,x))
#define PAin(x) 	MEM_ADDR(BITBAND(GPIOA_IDR,x))
#define PBout(x)	MEM_ADDR(BITBAND(GPIOB_ODR,x))
#define PBin(x) 	MEM_ADDR(BITBAND(GPIOB_IDR,x))
#define PCout(x) 	MEM_ADDR(BITBAND(GPIOC_ODR,x))
#define PCin(x) 	MEM_ADDR(BITBAND(GPIOC_IDR,x))
#define PDout(x) 	MEM_ADDR(BITBAND(GPIOD_ODR,x))
#define PDin(x)		MEM_ADDR(BITBAND(GPIOD_IDR,x))
#define PEout(x) 	MEM_ADDR(BITBAND(GPIOE_ODR,x))
#define PEin(x) 	MEM_ADDR(BITBAND(GPIOE_IDR,x))
#define PFout(x) 	MEM_ADDR(BITBAND(GPIOF_ODR,x))
#define PFin(x) 	MEM_ADDR(BITBAND(GPIOF_IDR,x))
#define PGout(x) 	MEM_ADDR(BITBAND(GPIOG_ODR,x))
#define PGin(x) 	MEM_ADDR(BITBAND(GPIOG_IDR,x))


/**
@code  
 The table below gives the allowed values of the pre-emption priority and subpriority according
 to the Priority Grouping configuration performed by NVIC_PriorityGroupConfig function
  ============================================================================================================================
    NVIC_PriorityGroup   | NVIC_IRQChannelPreemptionPriority | NVIC_IRQChannelSubPriority  | Description
  ============================================================================================================================
   NVIC_PriorityGroup_0  |                0                  |            0-15             |   0 bits for pre-emption priority
                         |                                   |                             |   4 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------
   NVIC_PriorityGroup_1  |                0-1                |            0-7              |   1 bits for pre-emption priority
                         |                                   |                             |   3 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_2  |                0-3                |            0-3              |   2 bits for pre-emption priority
                         |                                   |                             |   2 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_3  |                0-7                |            0-1              |   3 bits for pre-emption priority
                         |                                   |                             |   1 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_4  |                0-15               |            0                |   4 bits for pre-emption priority
                         |                                   |                             |   0 bits for subpriority                       
  ============================================================================================================================
@endcode
*/

//中断分组
#define NVIC_PriorityGroup_0         ((uint32_t)0x700) /*!< 0 bits for pre-emption priority
                                                            4 bits for subpriority */
#define NVIC_PriorityGroup_1         ((uint32_t)0x600) /*!< 1 bits for pre-emption priority
                                                            3 bits for subpriority */
#define NVIC_PriorityGroup_2         ((uint32_t)0x500) /*!< 2 bits for pre-emption priority
                                                            2 bits for subpriority */
#define NVIC_PriorityGroup_3         ((uint32_t)0x400) /*!< 3 bits for pre-emption priority
                                                            1 bits for subpriority */
#define NVIC_PriorityGroup_4         ((uint32_t)0x300) /*!< 4 bits for pre-emption priority
                                                            0 bits for subpriority */
void Set_NVICPriority(IRQn_Type IRQn,uint32_t PreemptPriority,uint32_t SubPriority);


#endif

