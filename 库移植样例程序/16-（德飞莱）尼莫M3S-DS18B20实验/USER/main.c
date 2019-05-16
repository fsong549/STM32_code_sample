/*-------------------------------------------------------------------------------
文件名称：main.c
文件描述：DS18B20温度测试
硬件平台：尼莫M3S开发板+DS18B20（三极管TO-92封装）芯片插反会导致发烫烧毁
编写整理：shifang
固件库  ：V3.5
技术论坛：www.doflye.net
备    注：通过简单修改可以移植到其他开发板，部分资料来源于网络。
---------------------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f10x.h"
#include "led.h"
#include "Delay.h"
#include "key.h"
#include "timer.h"
#include "beep.h"
#include "usart.h"
#include "adc.h"
#include "lcd.h"
#include "24cxx.h" 
#include "flash.h" 
#include "can.h"
#include "remote.h"
#include "ds18b20.h"

int main(void)
{		
	u8 t=0;			    
	short temperature;  
	
	LED_Init();//LED初始化
  KEY_Init();//按键初始化
  SysTick_Init();//延时初始化
  USART1_Int(9600);
	LCD_Init();
  printf("\n\r（德飞莱）尼莫M3S开发板TFT LCD DS18B20 温度测试程序\r");	 	 

 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"M3S STM32");	
	LCD_ShowString(60,70,200,16,16,"DS18B20 test");	
	LCD_ShowString(60,90,200,16,16,"www.doflye.net");
	LCD_ShowString(60,110,200,16,16,"Insert DS18B20 in U1");		  
 	while(DS18B20_Init())	//DS18B20初始化	
	{
		LCD_ShowString(60,130,200,16,16,"DS18B20 Error");
		Delay_ms(200);
		LCD_Fill(60,130,239,130+16,WHITE);
 		Delay_ms(200);
	}								   
	LCD_ShowString(60,130,200,16,16,"DS18B20 OK");
	POINT_COLOR=BLUE;//设置字体为蓝色 
 	LCD_ShowString(60,150,200,16,16,"Temperate:   . C");		 
 	while(1)
	{
	if(t%10==0)//每100ms读取一次
		{									  
			temperature=DS18B20_Get_Temp();	
			if(temperature<0)
			{
				LCD_ShowChar(60+80,150,'-',16,0);			//显示负号
				temperature=-temperature;					//转为正数
			}else LCD_ShowChar(60+80,150,' ',16,0);			//去掉负号
			LCD_ShowNum(60+80+8,150,temperature/10,2,16);	//显示正数部分	    
   			LCD_ShowNum(60+80+32,150,temperature%10,1,16);	//显示小数部分 		   
		}				   
	 	Delay_ms(10);
		t++;
		if(t==20)
		{
			t=0;
			LED2_REV;
		}
	}
}

/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
