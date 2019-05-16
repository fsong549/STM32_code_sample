/*-------------------------------------------------------------------------------
文件名称：main.c
文件描述：改变DAC1通道数值，反应到引脚PA4，用万用表或者示波器测量电压值
硬件平台：尼莫M3S开发板
编写整理：shifang
固件库  ：V3.5
技术论坛：www.doflye.net
备    注：通过简单修改可以移植到其他开发板，部分资料来源于网络。
---------------------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "timer.h"
#include "beep.h"
#include "usart.h"
#include "adc.h"
#include "tsensor.h"
#include "dac.h"
   

int main(void)
{
	u16 dac_temp = 0;

	
	LED_Init();//LED初始化
  KEY_Init();//按键初始化
  SysTick_Init();//延时初始化
	BEEP_Init();   //蜂鸣器初始化
  USART1_Int(9600);
	DAC1_Init();  //回环模式初始化		 	 

	
  printf("\n\rADC Test: （德飞莱）尼莫M3S开发板DAC1通道测试程序，PA4引脚输出\r");


      
	while(1)
	{
		DAC1_Set_Vol(dac_temp);
		dac_temp += 50;
		if(dac_temp == 4096)
			 dac_temp = 0;
  	Delay_ms(500);		  
    LED2_REV;	
  }
}

/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
