/*-------------------------------------------------------------------------------
文件名称：main.c
文件描述：SPI FLASH 基本测试
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
#include "flash.h" 

//要写入到SPI Flash的字符串数组
const u8 TEXT_Buffer[]={"M3S STM32 SPI TEST"};
#define SIZE sizeof(TEXT_Buffer)	 
int main(void)
{		
	u8 key;
	u16 i=0;
	u8 datatemp[SIZE];
	u32 FLASH_SIZE;
	LED_Init();//LED初始化
  KEY_Init();//按键初始化
  SysTick_Init();//延时初始化
	BEEP_Init();   //蜂鸣器初始化
  USART1_Int(9600);
	LCD_Init();
  printf("\n\r（德飞莱）尼莫M3S开发板TFT LCD SPI W25Qxx FLASH 测试程序\r");	 	
	AT24CXX_Init();			//IIC初始化 
	SPI_Flash_Init();  		//SPI FLASH 初始化 	  

 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"M3S STM32");	
	LCD_ShowString(60,70,200,16,16,"SPI test");	
	LCD_ShowString(60,90,200,16,16,"www.doflye.net");
	LCD_ShowString(60,110,200,16,16,"test W25Qxx Flash");	
	LCD_ShowString(60,130,200,16,16,"S2:Write  S3:Read");	//显示提示信息		
	while(SPI_Flash_ReadID()!=W25Q16 && SPI_Flash_ReadID()!=W25Q32 && SPI_Flash_ReadID()!=W25Q64)							//检测不到W25Q16、32、64
	{
		LCD_ShowString(60,150,200,16,16,"25Qxx Check Failed!");
		Delay_ms(500);
		LCD_ShowString(60,150,200,16,16,"Please Check!      ");
		Delay_ms(500);
		LED2_REV;//LED2闪烁
	}
	LCD_ShowString(60,150,200,16,16,"25Qxx Ready!");

	FLASH_SIZE=8*1024*1024;	//FLASH 大小为8M字节
  	POINT_COLOR=BLUE;		//设置字体为蓝色	  
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY2)//S2按下,写入W25Q64
		{
			LCD_Fill(0,170,239,319,WHITE);//清除半屏    
 			LCD_ShowString(60,170,200,16,16,"Start Write W25Q64....");
			SPI_Flash_Write((u8*)TEXT_Buffer,FLASH_SIZE-100,SIZE);		//从倒数第100个地址处开始,写入SIZE长度的数据
			LCD_ShowString(60,170,200,16,16,"W25Q64 Write Finished!");	//提示传送完成
		}
		if(key==KEY3)//KS3按下,读取字符串并显示
		{
 			LCD_ShowString(60,170,200,16,16,"Start Read W25Q64.... ");
			SPI_Flash_Read(datatemp,FLASH_SIZE-100,SIZE);				//从倒数第100个地址处开始,读出SIZE个字节
			LCD_ShowString(60,170,200,16,16,"The Data Readed Is:  ");	//提示传送完成
			LCD_ShowString(60,190,200,16,16,datatemp);					//显示读到的字符串
		}
		i++;
		Delay_ms(10);
		if(i==20)
		{
			LED2_REV;//提示系统正在运行	
			i=0;
		}		   
	}
}

/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
