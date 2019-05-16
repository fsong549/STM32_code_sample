#ifndef __SPI_H
#define __SPI_H
#include "stm32f10x.h"
/*-------------------------------------------------------------------------------
文件名称：main.c
文件描述：SPI时序
硬件平台：尼莫M3S开发板
编写整理：shifang
固件库  ：V3.5
技术论坛：www.doflye.net
备    注：通过简单修改可以移植到其他开发板，部分资料来源于网络。
---------------------------------------------------------------------------------*/

 
 				  	    													  
void SPI2_Init(void);			 //初始化SPI口
void SPI2_SetSpeed(u8 SpeedSet); //设置SPI速度   
u8 SPI2_ReadWriteByte(u8 TxData);//SPI总线读写一个字节
		 
#endif

/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
