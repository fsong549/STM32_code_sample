/*-------------------------------------------------------------------------------
文件名称：main.c
文件描述：SPI CAN 功能 基本测试
硬件平台：尼莫M3S开发板+CAN驱动模块 2套，加传输线若干
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


int main(void)
{		
	u8 key;
	u8 i=0,t=0;
	u8 cnt=0;
	u8 canbuf[8];
	u8 res;
	u8 mode=1;//CAN工作模式;0,普通模式;1,环回模式
	
	LED_Init();//LED初始化
  KEY_Init();//按键初始化
  SysTick_Init();//延时初始化
	BEEP_Init();   //蜂鸣器初始化
  USART1_Int(9600);
	LCD_Init();
  printf("\n\r（德飞莱）尼莫M3S开发板TFT LCD CAN mode 测试程序\r");	 	
	CAN_Mode_Init(1,8,7,5,mode);//CAN初始化,波特率450Kbps    

 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"M3S STM32");	
	LCD_ShowString(60,70,200,16,16,"CAN test");	
	LCD_ShowString(60,90,200,16,16,"need 2 M3S board");
	LCD_ShowString(60,110,200,16,16,"and 2 VP230 board");
	LCD_ShowString(60,130,200,16,16,"LoopBack Mode");	 
	LCD_ShowString(60,150,200,16,16,"S1:Send S2:Mode");//显示提示信息		
  	POINT_COLOR=BLUE;//设置字体为蓝色	  
	LCD_ShowString(60,170,200,16,16,"Count:");			//显示当前计数值	
	LCD_ShowString(60,190,200,16,16,"Send Data:");		//提示发送的数据	
	LCD_ShowString(60,250,200,16,16,"Receive Data:");	//提示接收到的数据		
 	while(1)
	{
		key=KEY_Scan(0);
	 if(key==KEY1)//S1按下,发送一次数据
		{
			for(i=0;i<8;i++)
			{
				canbuf[i]=cnt+i;//填充发送缓冲区
				if(i<4)LCD_ShowxNum(60+i*32,210,canbuf[i],3,16,0X80);	//显示数据
				else LCD_ShowxNum(60+(i-4)*32,230,canbuf[i],3,16,0X80);	//显示数据
 			}
			res=Can_Send_Msg(canbuf,8);//发送8个字节 
			if(res)LCD_ShowString(60+80,190,200,16,16,"Failed");		//提示发送失败
			else LCD_ShowString(60+80,190,200,16,16,"OK    ");	 		//提示发送成功								   
		}
		else if(key==KEY2)//S2按下，改变CAN的工作模式
		{	   
			mode=!mode;
			CAN_Mode_Init(1,8,7,5,mode);//CAN普通模式初始化,普通模式,波特率450Kbps
  			POINT_COLOR=RED;//设置字体为红色 
			if(mode==0)//普通模式，需要2个开发板
			{
				LCD_ShowString(60,130,200,16,16,"Nnormal Mode ");	    
			}else //回环模式,一个开发板就可以测试了.
			{
 				LCD_ShowString(60,130,200,16,16,"LoopBack Mode");
			}
 			POINT_COLOR=BLUE;//设置字体为蓝色 
		}		 
		key=Can_Receive_Msg(canbuf);
		if(key)//接收到有数据
		{			
			LCD_Fill(60,270,130,310,WHITE);//清除之前的显示
 			for(i=0;i<key;i++)
			{									    
				if(i<4)LCD_ShowxNum(60+i*32,270,canbuf[i],3,16,0X80);	//显示数据
				else LCD_ShowxNum(60+(i-4)*32,290,canbuf[i],3,16,0X80);	//显示数据
 			}
		}
		t++; 
		Delay_ms(10);
		if(t==20)
		{
			LED2_REV;//提示系统正在运行	
			t=0;
			cnt++;
			LCD_ShowxNum(60+48,170,cnt,3,16,0X80);	//显示数据
		}		   
	}
}

/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
