#include "sys.h"

//�����ж�
void Set_NVICPriority(IRQn_Type IRQn,uint32_t PreemptPriority,uint32_t SubPriority)
{
	uint32_t Priority;
	//�����жϷ���
	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2);
	//����һ���ж�
	Priority = NVIC_EncodePriority (NVIC_PriorityGroup_2,PreemptPriority,SubPriority);
	//�����ж�
	NVIC_SetPriority(IRQn,Priority);
	//ʹ���ж���
	NVIC_EnableIRQ(IRQn);
}
