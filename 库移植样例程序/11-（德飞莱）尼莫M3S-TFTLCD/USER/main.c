/*-------------------------------------------------------------------------------
�ļ����ƣ�main.c
�ļ�������TFT LCD������ʾ
Ӳ��ƽ̨����ĪM3S������
��д����shifang
�̼���  ��V3.5
������̳��www.doflye.net
��    ע��ͨ�����޸Ŀ�����ֲ�����������壬����������Դ�����硣
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

// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue;

// �ֲ����������ڱ���ת�������ĵ�ѹֵ			 
float ADC_ConvertedValueLocal;     

int main(void)
{
	u8 x=0;
	u8 lcd_id[12];			//���LCD ID�ַ���
	LED_Init();//LED��ʼ��
  KEY_Init();//������ʼ��
  SysTick_Init();//��ʱ��ʼ��
	BEEP_Init();   //��������ʼ��
  USART1_Int(9600);
	LCD_Init();
  printf("\n\rADC Test: ���·�������ĪM3S������TFT LCD ���Գ���\r");
	POINT_COLOR=RED;
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id���顣				 	
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
 		LCD_ShowString(30,110,200,16,16,lcd_id);		//��ʾLCD ID	      					 
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

/*----------------------�·��� ������̳��www.doflye.net--------------------------*/
