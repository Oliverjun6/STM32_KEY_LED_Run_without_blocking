#include "stm32f10x.h"                  // Device header
#include "sys.h"   
#include "delay.h"
#include "Timer.h"

void TIM3_Int_Init(u16 arr,u16 psc)
{	
	TIM_TimeBaseInitTypeDef TIMER_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIMER_InitStruct.TIM_Period = arr;
	TIMER_InitStruct.TIM_Prescaler = psc;
	TIMER_InitStruct.TIM_CounterMode = TIM_CounterMode_Up ;
	TIMER_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3, &TIMER_InitStruct);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_Cmd(TIM3 ,ENABLE);
	
}

