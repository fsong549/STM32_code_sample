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
#include "Delay.h"
#include "key.h"
#include "timer.h"
#include "beep.h"
#include "usart.h"
#include "adc.h"
#include "lcd.h"
#include "24cxx.h" 

//Ҫд�뵽24c02���ַ�������
const u8 TEXT_Buffer[]={"M3S STM32 IIC TEST"};
#define SIZE sizeof(TEXT_Buffer)	 
int main(void)
{		
	u8 key;
	u16 i=0;
	u8 datatemp[SIZE];
	LED_Init();//LED��ʼ��
  KEY_Init();//������ʼ��
  SysTick_Init();//��ʱ��ʼ��
	BEEP_Init();   //��������ʼ��
  USART1_Int(9600);
	LCD_Init();
  printf("\n\rADC Test: ���·�������ĪM3S������TFT LCD IIC 24Cxx ���Գ���\r");	 	
	AT24CXX_Init();			//IIC��ʼ�� 

 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"M3S STM32");	
	LCD_ShowString(60,70,200,16,16,"IIC test");	
	LCD_ShowString(60,90,200,16,16,"www.doflye.net");
	LCD_ShowString(60,110,200,16,16,"for IC 24c02 ");	
	LCD_ShowString(60,130,200,16,16,"S4:Write  S2:Read");	//��ʾ��ʾ��Ϣ		
 	while(AT24CXX_Check())//��ⲻ��24c02
	{
		LCD_ShowString(60,150,200,16,16,"24C02 Check Failed!");
		Delay_ms(500);
		LCD_ShowString(60,150,200,16,16,"Please Check!      ");
		Delay_ms(500);
		LED2_REV;
	}
	LCD_ShowString(60,150,200,16,16,"24C02 Ready!");    
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ	  
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY4)//S4����,д��24C02
		{
			LCD_Fill(0,170,239,319,WHITE);//�������    
 			LCD_ShowString(60,170,200,16,16,"Start Write 24C02....");
			AT24CXX_Write(0,(u8*)TEXT_Buffer,SIZE);
			LCD_ShowString(60,170,200,16,16,"24C02 Write Finished!");//��ʾ�������
		}
		if(key==KEY2)//S2����,��ȡ�ַ�������ʾ
		{
 			LCD_ShowString(60,170,200,16,16,"Start Read 24C02.... ");
			AT24CXX_Read(0,datatemp,SIZE);
			LCD_ShowString(60,170,200,16,16,"The Data Readed Is:  ");//��ʾ�������
			LCD_ShowString(60,190,200,16,16,datatemp);//��ʾ�������ַ���
		}
		i++;
		Delay_ms(10);
		if(i==20)
		{
			LED2_REV;
			i=0;
		}		   
	}
}

/*----------------------�·��� ������̳��www.doflye.net--------------------------*/
