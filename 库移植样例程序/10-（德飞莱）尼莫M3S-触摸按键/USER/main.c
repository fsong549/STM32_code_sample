/*-------------------------------------------------------------------------------
文件名称：main.c
文件描述：J13插入跳帽，SD2 卡座外壳作为触摸键盘，通过触摸改变LED2状态
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
#include "tpad.h"   

int main(void)
{
	u8 t = 0;

	
	LED_Init();//LED初始化
  KEY_Init();//按键初始化
  SysTick_Init();//延时初始化
	BEEP_Init();   //蜂鸣器初始化
  USART1_Int(9600);
	TPAD_Init();			//???????	 	 

	
  printf("\n\rADC Test: （德飞莱）尼莫M3S开发板DAC1通道测试程序，PA4引脚输出\r");


      
  
  while(1)
	{					  						  		 
 		if(TPAD_Scan(0))	//???????????(?????????15ms)
		{
			LED2_REV;		//LED1??
		}
		t++;
		if(t==15)		 
		{
			t=0;
			LED3_REV;		//LED0??,????????
		}
		Delay_ms(10);
	}	

  
}

/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
