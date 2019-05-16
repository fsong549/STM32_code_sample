/*-------------------------------------------------------------------------------
文件名称：main.c
文件描述：通过串口1，打印内部温度传感器的数值
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
   

int main(void)
{
	u16 adcx;
	float temp;
 	float temperate;
	
	LED_Init();//LED初始化
  KEY_Init();//按键初始化
  SysTick_Init();//延时初始化
	BEEP_Init();   //蜂鸣器初始化
  USART1_Int(9600);
	T_Adc_Init();
	
  printf("\n\rADC Test: （德飞莱）尼莫M3S开发板ADC内部温度转换测试程序\r");


      
	while(1)
	{
		adcx=T_Get_Adc_Average(ADC_CH_TEMP,10);
		temp=(float)adcx*(3.3/4096);
		temperate=temp;//保存温度传感器的电压值								  
		temperate=(1.43-temperate)/0.0043+25;		//计算出当前温度值	 
	//使用printf函数循环发送固定信息
  
	  printf("\r\n 采集数值16进制 = 0x%04X \r\n", adcx); 
	  printf("\r\n 转换后的实际温度 = %f C \r\n",temperate); 
  	Delay_ms(500);		  
    LED2_REV;	
  }
}

/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
