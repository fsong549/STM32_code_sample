/*-------------------------------------------------------------------------------
文件名称：main.c
文件描述：TFT LCD基本显示
硬件平台：尼莫M3S开发板
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

//要写入到24c02的字符串数组
const u8 TEXT_Buffer[]={"M3S STM32 IIC TEST"};
#define SIZE sizeof(TEXT_Buffer)	 
int main(void)
{		
	u8 key;
	u16 i=0;
	u8 datatemp[SIZE];
	LED_Init();//LED初始化
  KEY_Init();//按键初始化
  SysTick_Init();//延时初始化
	BEEP_Init();   //蜂鸣器初始化
  USART1_Int(9600);
	LCD_Init();
  printf("\n\rADC Test: （德飞莱）尼莫M3S开发板TFT LCD IIC 24Cxx 测试程序\r");	 	
	AT24CXX_Init();			//IIC初始化 

 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"M3S STM32");	
	LCD_ShowString(60,70,200,16,16,"IIC test");	
	LCD_ShowString(60,90,200,16,16,"www.doflye.net");
	LCD_ShowString(60,110,200,16,16,"for IC 24c02 ");	
	LCD_ShowString(60,130,200,16,16,"S4:Write  S2:Read");	//显示提示信息		
 	while(AT24CXX_Check())//检测不到24c02
	{
		LCD_ShowString(60,150,200,16,16,"24C02 Check Failed!");
		Delay_ms(500);
		LCD_ShowString(60,150,200,16,16,"Please Check!      ");
		Delay_ms(500);
		LED2_REV;
	}
	LCD_ShowString(60,150,200,16,16,"24C02 Ready!");    
 	POINT_COLOR=BLUE;//设置字体为蓝色	  
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY4)//S4按下,写入24C02
		{
			LCD_Fill(0,170,239,319,WHITE);//清除半屏    
 			LCD_ShowString(60,170,200,16,16,"Start Write 24C02....");
			AT24CXX_Write(0,(u8*)TEXT_Buffer,SIZE);
			LCD_ShowString(60,170,200,16,16,"24C02 Write Finished!");//提示传送完成
		}
		if(key==KEY2)//S2按下,读取字符串并显示
		{
 			LCD_ShowString(60,170,200,16,16,"Start Read 24C02.... ");
			AT24CXX_Read(0,datatemp,SIZE);
			LCD_ShowString(60,170,200,16,16,"The Data Readed Is:  ");//提示传送完成
			LCD_ShowString(60,190,200,16,16,datatemp);//显示读到的字符串
		}
		i++;
		Delay_ms(10);
		if(i==20)
		{
			LED2_REV;
			i=0;
		}		   
	}
}

/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
