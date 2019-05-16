/*-------------------------------------------------------------------------------
文件名称：main.c
文件描述：RF24L01测试
硬件平台：尼莫M3S开发板+RF24L01 2套
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

int main(void)
{		
	u8 key,mode;
	u16 t=0;			 
	u8 tmp_buf[33];
	
	LED_Init();//LED初始化
  KEY_Init();//按键初始化
  SysTick_Init();//延时初始化
  USART1_Int(9600);
	LCD_Init();
  printf("\n\r（德飞莱）尼莫M3S开发板TFT LCD NRF24L01 无线传输测试程序\r");	 	 

  NRF24L01_Init();    	//初始化NRF24L01 

 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"M3S STM32");	
	LCD_ShowString(60,70,200,16,16,"NRF24L01 test");	
	LCD_ShowString(60,90,200,16,16,"www.doflye.net");
	LCD_ShowString(60,110,200,16,16,"use 2 M3S board");		  
 	while(NRF24L01_Check())	//检查NRF24L01是否在位.	
	{
		LCD_ShowString(60,130,200,16,16,"NRF24L01 Error");
		Delay_ms(200);
		LCD_Fill(60,130,239,130+16,WHITE);
 		Delay_ms(200);
	}								   
	LCD_ShowString(60,130,200,16,16,"NRF24L01 OK");	 
 	while(1)
	{
	key=KEY_Scan(0);
		if(key==KEY1)
		{
			mode=0;   
			break;
		}else if(key==KEY2)
		{
			mode=1;
			break;
		}
		t++;
		if(t==100)LCD_ShowString(10,150,230,16,16,"S1:RX_Mode  S2:TX_Mode"); //闪烁显示提示信息
 		if(t==200)
		{	
			LCD_Fill(10,150,230,150+16,WHITE);
			t=0; 
		}
		Delay_ms(5);	  
	}   
 	LCD_Fill(10,150,240,166,WHITE);//清空上面的显示		  
 	POINT_COLOR=BLUE;//设置字体为蓝色	   
	if(mode==0)//RX模式
	{
		LCD_ShowString(60,150,200,16,16,"NRF24L01 RX_Mode");	
		LCD_ShowString(60,170,200,16,16,"Received DATA:");	
		NRF24L01_RX_Mode();		  
		while(1)
		{	  		    		    				 
			if(NRF24L01_RxPacket(tmp_buf)==0)//一旦接收到信息,则显示出来.
			{
				tmp_buf[32]=0;//加入字符串结束符
				LCD_ShowString(0,190,239,32,16,tmp_buf);    
			}else Delay_us(100);	   
			t++;
			if(t==10000)//大约1s钟改变一次状态
			{
				t=0;
				LED2_REV;
			} 				    
		};	
	}else//TX模式
	{							    
		LCD_ShowString(60,150,200,16,16,"NRF24L01 TX_Mode");	
		NRF24L01_TX_Mode();
		mode=' ';//从空格键开始  
		while(1)
		{	  		   				 
			if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
			{
				LCD_ShowString(60,170,239,32,16,"Sended DATA:");	
				LCD_ShowString(0,190,239,32,16,tmp_buf); 
				key=mode;
				for(t=0;t<32;t++)
				{
					key++;
					if(key>('~'))key=' ';
					tmp_buf[t]=key;	
				}
				mode++; 
				if(mode>'~')mode=' ';  	  
				tmp_buf[32]=0;//加入结束符		   
			}else
			{										   	
 				LCD_ShowString(60,170,239,32,16,"Send Failed "); 
				LCD_Fill(0,188,240,218,WHITE);//清空上面的显示			   
			};
			LED2_REV;
			Delay_ms(1500);				    
		};
	}
}

/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
