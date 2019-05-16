/*-------------------------------------------------------------------------------
�ļ����ƣ�main.c
�ļ�������SPI FLASH ��������
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
#include "flash.h" 

//Ҫд�뵽SPI Flash���ַ�������
const u8 TEXT_Buffer[]={"M3S STM32 SPI TEST"};
#define SIZE sizeof(TEXT_Buffer)	 
int main(void)
{		
	u8 key;
	u16 i=0;
	u8 datatemp[SIZE];
	u32 FLASH_SIZE;
	LED_Init();//LED��ʼ��
  KEY_Init();//������ʼ��
  SysTick_Init();//��ʱ��ʼ��
	BEEP_Init();   //��������ʼ��
  USART1_Int(9600);
	LCD_Init();
  printf("\n\r���·�������ĪM3S������TFT LCD SPI W25Qxx FLASH ���Գ���\r");	 	
	AT24CXX_Init();			//IIC��ʼ�� 
	SPI_Flash_Init();  		//SPI FLASH ��ʼ�� 	  

 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"M3S STM32");	
	LCD_ShowString(60,70,200,16,16,"SPI test");	
	LCD_ShowString(60,90,200,16,16,"www.doflye.net");
	LCD_ShowString(60,110,200,16,16,"test W25Qxx Flash");	
	LCD_ShowString(60,130,200,16,16,"S2:Write  S3:Read");	//��ʾ��ʾ��Ϣ		
	while(SPI_Flash_ReadID()!=W25Q16 && SPI_Flash_ReadID()!=W25Q32 && SPI_Flash_ReadID()!=W25Q64)							//��ⲻ��W25Q16��32��64
	{
		LCD_ShowString(60,150,200,16,16,"25Qxx Check Failed!");
		Delay_ms(500);
		LCD_ShowString(60,150,200,16,16,"Please Check!      ");
		Delay_ms(500);
		LED2_REV;//LED2��˸
	}
	LCD_ShowString(60,150,200,16,16,"25Qxx Ready!");

	FLASH_SIZE=8*1024*1024;	//FLASH ��СΪ8M�ֽ�
  	POINT_COLOR=BLUE;		//��������Ϊ��ɫ	  
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY2)//S2����,д��W25Q64
		{
			LCD_Fill(0,170,239,319,WHITE);//�������    
 			LCD_ShowString(60,170,200,16,16,"Start Write W25Q64....");
			SPI_Flash_Write((u8*)TEXT_Buffer,FLASH_SIZE-100,SIZE);		//�ӵ�����100����ַ����ʼ,д��SIZE���ȵ�����
			LCD_ShowString(60,170,200,16,16,"W25Q64 Write Finished!");	//��ʾ�������
		}
		if(key==KEY3)//KS3����,��ȡ�ַ�������ʾ
		{
 			LCD_ShowString(60,170,200,16,16,"Start Read W25Q64.... ");
			SPI_Flash_Read(datatemp,FLASH_SIZE-100,SIZE);				//�ӵ�����100����ַ����ʼ,����SIZE���ֽ�
			LCD_ShowString(60,170,200,16,16,"The Data Readed Is:  ");	//��ʾ�������
			LCD_ShowString(60,190,200,16,16,datatemp);					//��ʾ�������ַ���
		}
		i++;
		Delay_ms(10);
		if(i==20)
		{
			LED2_REV;//��ʾϵͳ��������	
			i=0;
		}		   
	}
}

/*----------------------�·��� ������̳��www.doflye.net--------------------------*/
