#ifndef __TPAD_H
#define __TPAD_H
#include "stm32f10x.h"
extern vu16 tpad_default_val;
							   
	  
void TPAD_Reset(void);
u16  TPAD_Get_Val(void);
u16  TPAD_Get_MaxVal(u8 n);
u8   TPAD_Init(void);
u8   TPAD_Scan(u8 mode);
void TIM5_CH2_Cap_Init(u16 arr,u16 psc);    
#endif























