#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "timer.h"
#include "delay.h"

void Hard_Ware_Init()
{
	LED_Init();
	KEY_Init();//IO初始化
	delay_init();
	TIM3_Int_Init(72-1 , 1000-1);//开一个1ms的定时器
}
int main(void)
{	
	uint8_t key_num; 
	uint8_t key_1_sta_flag = 0 , key_0_sta_flag = 0 ;
	Hard_Ware_Init();
	while(1)
	{
		key_num = Get_Keynum();
		switch (key_num)
		{
			case 1:key_1_sta_flag = !key_1_sta_flag;break;
			case 2:key_0_sta_flag = !key_0_sta_flag;break;
			default:break;
		}
		if(key_1_sta_flag)
		{
			LED1_set_state(1);
		}
		else
		{
			LED1_set_state(0);
		}
		
		if(key_0_sta_flag)
		{
			LED0_set_state(1);
		}
		else
		{
			LED0_set_state(0);
		}


	}
}
 
void TIM3_IRQHandler(void) 
{
	if(TIM_GetITStatus(TIM3,  TIM_IT_Update) == SET)   //SET = 1
	{
		TIM_ClearITPendingBit(TIM3 , TIM_IT_Update);  //clear
		Key_tick();//每隔1ms进入一次tick
		LED_Tick();
	}
	
}