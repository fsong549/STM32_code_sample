#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "wkup.h"

//待机唤醒实验  
 int main(void)
 {	 
  
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
 	LED_Init();			     //LED端口初始化	 	
	WKUP_Init(); //待机唤醒初始化
	LCD_Init();	 //LCD初始化
	POINT_COLOR=RED;
	LCD_ShowString(30,50,200,16,16,"M3S STM32");	
	LCD_ShowString(30,70,200,16,16,"WKUP TEST");	
	LCD_ShowString(30,90,200,16,16,"www.doflye.net");
	LCD_ShowString(30,110,200,16,16,"press S4 3S to shutdown");
	while(1)
	{
		LED0=!LED0;
		delay_ms(250);
	}
 }

