
#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

#define S1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define S2 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define S3 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)
#define S4 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)

void KEY_Init(void);

#endif
/*----------------------�·��� ������̳��www.doflye.net--------------------------*/
