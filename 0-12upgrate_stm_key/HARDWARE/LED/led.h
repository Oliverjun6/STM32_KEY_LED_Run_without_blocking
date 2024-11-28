#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	
#define LED_RED PBout(5)
#define LED_GREEN PEout(5)
void LED_Init(void);
void LED1_set_state(uint8_t sta);
void LED0_set_state(uint8_t sta);	 				    
#endif
