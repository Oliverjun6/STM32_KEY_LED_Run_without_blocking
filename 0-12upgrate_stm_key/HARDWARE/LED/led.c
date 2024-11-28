#include "led.h"
#define led1_Counter 500//����۴�
#define led0_Counter 1000//��һǧ��
uint8_t led1_mod,led0_mod;
//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 �����

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 �˿�����, �������
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 ����� 
}
 
void LED_Tick()
{
	static uint16_t led1_count;
	static uint16_t led0_count;
	led1_count++;
	led0_count++;
	led1_count %= led1_Counter;
	led0_count %= led0_Counter;
	
	if(led1_mod == 0)
	{
		LED_RED = 1;
	}
	if(led1_mod == 1)
	{
		if(led1_count < led1_Counter / 2) 
		{
			LED_RED = 0;
		}
		else
		{	
			LED_RED = 1;
		}	
	}
	if(led0_mod == 0)
	{
		LED_GREEN = 1;
	}
	if(led0_mod == 1)
	{
		if(led0_count < led0_Counter / 2) 
		{
			LED_GREEN = 0;
		}
		else
		{	
			LED_GREEN = 1;
		}	
	}

}
void LED1_set_state(uint8_t sta)
{
	led1_mod = sta;
}
void LED0_set_state(uint8_t sta)
{
	led0_mod = sta;
}