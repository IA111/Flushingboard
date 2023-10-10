#include "sys.h"

//设置中断
void Set_NVICPriority(IRQn_Type IRQn,uint32_t PreemptPriority,uint32_t SubPriority)
{
	uint32_t Priority;
	//设置中断分组
	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2);
	//返回一个中断
	Priority = NVIC_EncodePriority (NVIC_PriorityGroup_2,PreemptPriority,SubPriority);
	//设置中断
	NVIC_SetPriority(IRQn,Priority);
	//使能中断线
	NVIC_EnableIRQ(IRQn);
}
