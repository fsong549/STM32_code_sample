/*-------------------------------------------------------------------------------
文件名称：main.c
文件描述：SPI 模式SD卡测试 
硬件平台：尼莫M3S开发板+TF卡或者micro SD卡  使用SD2卡座，可能有部分卡不识别
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
#include "24l01.h"
#include "mmc_sd.h"	
#include "malloc.h"

int main(void)
{		
	u8 key;		 
	u32 sd_size;
	u8 t=0;	
	u8 *buf;
	
	LED_Init();//LED初始化
  KEY_Init();//按键初始化
  SysTick_Init();//延时初始化
  USART1_Int(9600);
	LCD_Init();
  printf("\n\r（德飞莱）尼莫M3S开发板TFT LCD SD卡测试 SPI模式测试程序\r");	 	 

  POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"M3S STM32");	
	LCD_ShowString(60,70,200,16,16,"SD CARD TEST");	
	LCD_ShowString(60,90,200,16,16,"www.doflye.net");
	LCD_ShowString(60,110,200,16,16,"insert SD2 card");  
	LCD_ShowString(60,130,200,16,16,"S1:Read Sector 0");	   
 	while(SD_Initialize())//检测不到SD卡
	{
		LCD_ShowString(60,150,200,16,16,"SD Card Error!");
		Delay_ms(500);					
		LCD_ShowString(60,150,200,16,16,"Please Check! ");
		Delay_ms(500);
		LED2_REV;//LED2闪烁
	}
 	POINT_COLOR=BLUE;//设置字体为蓝色 
	//检测SD卡成功 											    
	LCD_ShowString(60,150,200,16,16,"SD Card OK    ");
	LCD_ShowString(60,170,200,16,16,"SD Card Size:     MB");
	sd_size=SD_GetSectorCount();//得到扇区数
	LCD_ShowNum(164,170,sd_size>>11,5,16);//显示SD卡容量
 while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1)//S1按下了
		{
			buf=mymalloc(0,512);		//申请内存
			if(SD_ReadDisk(buf,0,1)==0)	//读取0扇区的内容
			{	
				LCD_ShowString(60,190,200,16,16,"USART1 Sending Data...");
				printf("SECTOR 0 DATA:\r\n");
				for(sd_size=0;sd_size<512;sd_size++)printf("%x ",buf[sd_size]);//打印0扇区数据    	   
				printf("\r\nDATA ENDED\r\n");
				LCD_ShowString(60,190,200,16,16,"USART1 Send Data Over!");
			}
			myfree(0,buf);//释放内存	   
		}   
		t++;
		Delay_ms(10);
		if(t==20)
		{
			LED2_REV;
			t=0;
		}
	}   
}

/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
