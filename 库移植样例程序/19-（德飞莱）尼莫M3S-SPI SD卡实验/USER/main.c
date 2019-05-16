/*-------------------------------------------------------------------------------
�ļ����ƣ�main.c
�ļ�������SPI ģʽSD������ 
Ӳ��ƽ̨����ĪM3S������+TF������micro SD��  ʹ��SD2�����������в��ֿ���ʶ��
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
#include "24l01.h"
#include "mmc_sd.h"	
#include "malloc.h"

int main(void)
{		
	u8 key;		 
	u32 sd_size;
	u8 t=0;	
	u8 *buf;
	
	LED_Init();//LED��ʼ��
  KEY_Init();//������ʼ��
  SysTick_Init();//��ʱ��ʼ��
  USART1_Int(9600);
	LCD_Init();
  printf("\n\r���·�������ĪM3S������TFT LCD SD������ SPIģʽ���Գ���\r");	 	 

  POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"M3S STM32");	
	LCD_ShowString(60,70,200,16,16,"SD CARD TEST");	
	LCD_ShowString(60,90,200,16,16,"www.doflye.net");
	LCD_ShowString(60,110,200,16,16,"insert SD2 card");  
	LCD_ShowString(60,130,200,16,16,"S1:Read Sector 0");	   
 	while(SD_Initialize())//��ⲻ��SD��
	{
		LCD_ShowString(60,150,200,16,16,"SD Card Error!");
		Delay_ms(500);					
		LCD_ShowString(60,150,200,16,16,"Please Check! ");
		Delay_ms(500);
		LED2_REV;//LED2��˸
	}
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
	//���SD���ɹ� 											    
	LCD_ShowString(60,150,200,16,16,"SD Card OK    ");
	LCD_ShowString(60,170,200,16,16,"SD Card Size:     MB");
	sd_size=SD_GetSectorCount();//�õ�������
	LCD_ShowNum(164,170,sd_size>>11,5,16);//��ʾSD������
 while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1)//S1������
		{
			buf=mymalloc(0,512);		//�����ڴ�
			if(SD_ReadDisk(buf,0,1)==0)	//��ȡ0����������
			{	
				LCD_ShowString(60,190,200,16,16,"USART1 Sending Data...");
				printf("SECTOR 0 DATA:\r\n");
				for(sd_size=0;sd_size<512;sd_size++)printf("%x ",buf[sd_size]);//��ӡ0��������    	   
				printf("\r\nDATA ENDED\r\n");
				LCD_ShowString(60,190,200,16,16,"USART1 Send Data Over!");
			}
			myfree(0,buf);//�ͷ��ڴ�	   
		}   
		t++;
		Delay_ms(10);
		if(t==20)
		{
			LED2_REV;
			t=0;
		}
	}   
}

/*----------------------�·��� ������̳��www.doflye.net--------------------------*/
