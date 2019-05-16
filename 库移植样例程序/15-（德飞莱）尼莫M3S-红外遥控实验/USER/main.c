/*-------------------------------------------------------------------------------
�ļ����ƣ�main.c
�ļ�������TC9012 ϵ�к���ң��������ʵ��
Ӳ��ƽ̨����ĪM3S������+��������ң����
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


int main(void)
{		
	u8 key;
	u8 t=0;	
	u8 *str=0;
	
	LED_Init();//LED��ʼ��
  KEY_Init();//������ʼ��
  SysTick_Init();//��ʱ��ʼ��
  USART1_Int(9600);
	LCD_Init();
  printf("\n\r���·�������ĪM3S������TFT LCD CAN mode ���Գ���\r");	 	 

 	Remote_Init();			//������ճ�ʼ��		 	
 
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"M3S STM32");	
	LCD_ShowString(60,70,200,16,16,"REMOTE test");	
	LCD_ShowString(60,90,200,16,16,"www.doflye.net");
	LCD_ShowString(60,110,200,16,16,"TC9012 IC");

  LCD_ShowString(60,130,200,16,16,"KEYVAL:");	
  LCD_ShowString(60,150,200,16,16,"KEYCNT:");	
  LCD_ShowString(60,170,200,16,16,"SYMBOL:");	 
 	while(1)
	{
	key=Remote_Scan();	
		if(key)
		{	 
			LCD_ShowNum(116,130,key,3,16);		//��ʾ��ֵ
			LCD_ShowNum(116,150,RmtCnt,3,16);	//��ʾ��������		  
			switch(key)
			{
				case 0:str="ERROR";break;			   
				case 162:str="CH-";break;	    
				case 98:str="CH";break;	    
				case 2:str="NEXT";break;		 
				case 226:str="CH+";break;		  
				case 194:str="PLAY";break;	   
				case 34:str="PREV";break;		  
				case 224:str="VOL-";break;		  
				case 168:str="VOL+";break;		   
				case 144:str="EQ";break;		    
				case 104:str="0";break;		  
				case 152:str="FL-";break;	   
				case 176:str="FL+";break;	    
				case 48:str="1";break;		    
				case 24:str="2";break;		    
				case 122:str="3";break;		  
				case 16:str="4";break;			   					
				case 56:str="5";break;	 
				case 90:str="6";break;
				case 66:str="7";break;
				case 74:str="8";break;
				case 82:str="9";break;		 
			}
			LCD_Fill(116,170,116+8*8,170+16,WHITE);	//���֮ǰ����ʾ
			LCD_ShowString(116,170,200,16,16,str);	//��ʾSYMBOL
		}
		else Delay_ms(10);	  
		t++;
		if(t==20)
		{
			t=0;
			LED2_REV;
		}
	}
}

/*----------------------�·��� ������̳��www.doflye.net--------------------------*/
