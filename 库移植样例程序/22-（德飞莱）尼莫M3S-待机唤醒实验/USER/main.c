#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "wkup.h"

//��������ʵ��  
 int main(void)
 {	 
  
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��	 	
	WKUP_Init(); //�������ѳ�ʼ��
	LCD_Init();	 //LCD��ʼ��
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

