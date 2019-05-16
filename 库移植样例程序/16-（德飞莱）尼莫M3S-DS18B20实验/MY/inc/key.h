
#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

#define S1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define S2 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define S3 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)
#define S4 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)

#define KEY4 	4
#define KEY3	3
#define KEY2	2
#define KEY1	1

void KEY_Init(void);
u8 KEY_Scan(u8 mode);
#endif
/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
