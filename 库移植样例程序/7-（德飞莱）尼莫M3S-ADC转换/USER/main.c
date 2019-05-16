/*-------------------------------------------------------------------------------
文件名称：main.c
文件描述：通过串口1，打印ADC1电压值（PC1）
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

// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue;

// 局部变量，用于保存转换计算后的电压值			 
float ADC_ConvertedValueLocal;     

int main(void)
{
	LED_Init();//LED初始化
  KEY_Init();//按键初始化
  SysTick_Init();//延时初始化
	BEEP_Init();   //蜂鸣器初始化
  USART1_Int(9600);
	ADC1_Init();
	
  printf("\n\rADC Test: （德飞莱）尼莫M3S开发板ADC转换测试程序\r");

  while (1)
  {
	//使用printf函数循环发送固定信息
  
	ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // 读取转换的AD值
	
	printf("\r\n 采集数值16进制 = 0x%04X \r\n", ADC_ConvertedValue); 
	printf("\r\n 转换后的实际电压值 = %f V \r\n",ADC_ConvertedValueLocal); 
	Delay_ms(500);		  
  LED2_REV;	
  }
}

/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
