#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	
#include "usmart.h"	 
#include "rtc.h" 

 int main(void)
 {	 
 	u8 t=0;	
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();			 	
	usmart_dev.init(SystemCoreClock/1000000);	//��ʼ��USMART	
	RTC_Init();	  			//RTC��ʼ��
	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"M3S STM32");	
	LCD_ShowString(60,70,200,16,16,"RTC test");	
	LCD_ShowString(60,90,200,16,16,"www.doflye.net");
	LCD_ShowString(60,110,200,16,16,"use backup battery");	
	while(RTC_Init())		//RTC��ʼ��	��һ��Ҫ��ʼ���ɹ�
	{ 
		LCD_ShowString(60,130,200,16,16,"RTC ERROR!   ");	
		delay_ms(800);
		LCD_ShowString(60,130,200,16,16,"RTC Trying...");	
	}		    						
	//��ʾʱ��
	POINT_COLOR=BLUE;//��������Ϊ��ɫ					 
	LCD_ShowString(60,130,200,16,16,"    -  -     ");	   
	LCD_ShowString(60,172,200,16,16,"  :  :  ");		    
	while(1)
	{								    
				if(t!=calendar.sec)
		{
			t=calendar.sec;
			LCD_ShowxNum(60,130,calendar.w_year,4,16,0x80);									  
			LCD_ShowxNum(100,130,calendar.w_month,2,16,0x80);									  
			LCD_ShowxNum(124,130,calendar.w_date,2,16,0x80);	 
			switch(calendar.week)
			{
				case 0:
					LCD_ShowString(60,148,200,16,16,"Sunday   ");
					break;
				case 1:
					LCD_ShowString(60,148,200,16,16,"Monday   ");
					break;
				case 2:
					LCD_ShowString(60,148,200,16,16,"Tuesday  ");
					break;
				case 3:
					LCD_ShowString(60,148,200,16,16,"Wednesday");
					break;
				case 4:
					LCD_ShowString(60,148,200,16,16,"Thursday ");
					break;
				case 5:
					LCD_ShowString(60,148,200,16,16,"Friday   ");
					break;
				case 6:
					LCD_ShowString(60,148,200,16,16,"Saturday ");
					break;  
			}
			LCD_ShowxNum(60,172,calendar.hour,2,16,0x80);									  
			LCD_ShowxNum(84,172,calendar.min,2,16,0x80);									  
			LCD_ShowxNum(108,172,calendar.sec,2,16,0x80);
			LED0=!LED0;
		}	
		delay_ms(10);		  
	};  
 }

