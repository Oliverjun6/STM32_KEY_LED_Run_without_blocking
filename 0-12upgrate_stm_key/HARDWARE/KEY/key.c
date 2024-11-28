#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
		
uint8_t Key_Num;		
//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_3;//KEY0-KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE4,3

	//��ʼ�� WK_UP-->GPIOA.0	  ��������
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0���ó����룬Ĭ������	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0

}
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY3���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY0==0||KEY1==0||WK_UP==1))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(WK_UP==1)return WKUP_PRES;
	}else if(KEY0==1&&KEY1==1&&WK_UP==0)key_up=1; 	    
 	return 0;// �ް�������
}

uint8_t Get_Keynum(void)
{
	uint8_t temp;
	if(Key_Num !=0 )
	{
		temp = Key_Num;
		Key_Num = 0;
		return temp;
	}
	return 0;
}

uint8_t Get_Keystate(void)
{
	if(GPIO_ReadInputDataBit(GPIOE , GPIO_Pin_3) == 0)//KEY1
	{
		return 1;
	}
	if(GPIO_ReadInputDataBit(GPIOE , GPIO_Pin_4) == 0)
	{
		return 2;
	}
	
	return 0;
}

void Key_tick(void)
{
	static uint8_t count;
	static uint8_t Current_sta;
	static uint8_t Pre_sta;
	count++;
	if(count == 20)
	{
		count = 0;
		Pre_sta = Current_sta;
		Current_sta = Get_Keystate();
		if(Current_sta == 0 && Pre_sta != 0)//���������ɿ�������
		{
			Key_Num = Pre_sta;
		}
	}
}

