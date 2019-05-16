/*-------------------------------------------------------------------------------
�ļ����ƣ�main.c
�ļ�������DS18B20�¶Ȳ���
Ӳ��ƽ̨����ĪM3S������+DS18B20��������TO-92��װ��оƬ�巴�ᵼ�·����ջ�
��д����shifang
�̼���  ��V3.5
������̳��www.doflye.net
��    ע��ͨ�����޸Ŀ�����ֲ�����������壬����������Դ�����硣
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
	
	LED_Init();//LED��ʼ��
  KEY_Init();//������ʼ��
  SysTick_Init();//��ʱ��ʼ��
  USART1_Int(9600);
	LCD_Init();
  printf("\n\r���·�������ĪM3S������TFT LCD DS18B20 �¶Ȳ��Գ���\r");	 	 

 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"M3S STM32");	
	LCD_ShowString(60,70,200,16,16,"DS18B20 test");	
	LCD_ShowString(60,90,200,16,16,"www.doflye.net");
	LCD_ShowString(60,110,200,16,16,"Insert DS18B20 in U1");		  
 	while(DS18B20_Init())	//DS18B20��ʼ��	
	{
		LCD_ShowString(60,130,200,16,16,"DS18B20 Error");
		Delay_ms(200);
		LCD_Fill(60,130,239,130+16,WHITE);
 		Delay_ms(200);
	}								   
	LCD_ShowString(60,130,200,16,16,"DS18B20 OK");
	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
 	LCD_ShowString(60,150,200,16,16,"Temperate:   . C");		 
 	while(1)
	{
	if(t%10==0)//ÿ100ms��ȡһ��
		{									  
			temperature=DS18B20_Get_Temp();	
			if(temperature<0)
			{
				LCD_ShowChar(60+80,150,'-',16,0);			//��ʾ����
				temperature=-temperature;					//תΪ����
			}else LCD_ShowChar(60+80,150,' ',16,0);			//ȥ������
			LCD_ShowNum(60+80+8,150,temperature/10,2,16);	//��ʾ��������	    
   			LCD_ShowNum(60+80+32,150,temperature%10,1,16);	//��ʾС������ 		   
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

/*----------------------�·��� ������̳��www.doflye.net--------------------------*/
