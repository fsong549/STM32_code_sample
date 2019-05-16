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
#include "delay.h"
#include "key.h"
#include "timer.h"
#include "beep.h"
#include "usart.h"
#include "adc.h"
#include "lcd.h"

// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue;

// 局部变量，用于保存转换计算后的电压值			 
float ADC_ConvertedValueLocal;     

int main(void)
{
	u8 x=0;
	u8 lcd_id[12];			//存放LCD ID字符串
	LED_Init();//LED初始化
  KEY_Init();//按键初始化
  SysTick_Init();//延时初始化
	BEEP_Init();   //蜂鸣器初始化
  USART1_Int(9600);
	LCD_Init();
  printf("\n\rADC Test: （德飞莱）尼莫M3S开发板TFT LCD 测试程序\r");
	POINT_COLOR=RED;
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。				 	
  while(1) 
	{		 
		switch(x)
		{
			case 0:LCD_Clear(WHITE);break;
			case 1:LCD_Clear(BLACK);break;
			case 2:LCD_Clear(BLUE);break;
			case 3:LCD_Clear(RED);break;
			case 4:LCD_Clear(MAGENTA);break;
			case 5:LCD_Clear(GREEN);break;
			case 6:LCD_Clear(CYAN);break;

			case 7:LCD_Clear(YELLOW);break;
			case 8:LCD_Clear(BRRED);break;
			case 9:LCD_Clear(GRAY);break;
			case 10:LCD_Clear(LGRAY);break;
			case 11:LCD_Clear(BROWN);break;
		}
		POINT_COLOR=RED;	  
		LCD_ShowString(30,50,200,16,16,"M3S STM32 [^o^]");	
		LCD_ShowString(30,70,200,16,16,"TFT-LCD test");	
		LCD_ShowString(30,90,200,16,16,"www.doflye.net");
 		LCD_ShowString(30,110,200,16,16,lcd_id);		//显示LCD ID	      					 
		LCD_ShowString(30,130,200,16,16,"01234567890");	   
    LCD_ShowString(30,150,200,16,16,"abcdefgABCDEFG");	
		Draw_Circle(100,180,20);	
    Draw_Circle(100,180,25);	     					 
	    x++;
		if(x==12)x=0;
		LED2_REV;					 
		Delay_ms(1000);	
	} 
}

/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
