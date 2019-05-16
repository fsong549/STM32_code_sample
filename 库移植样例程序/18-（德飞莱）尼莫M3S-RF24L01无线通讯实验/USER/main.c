/*-------------------------------------------------------------------------------
�ļ����ƣ�main.c
�ļ�������RF24L01����
Ӳ��ƽ̨����ĪM3S������+RF24L01 2��
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

int main(void)
{		
	u8 key,mode;
	u16 t=0;			 
	u8 tmp_buf[33];
	
	LED_Init();//LED��ʼ��
  KEY_Init();//������ʼ��
  SysTick_Init();//��ʱ��ʼ��
  USART1_Int(9600);
	LCD_Init();
  printf("\n\r���·�������ĪM3S������TFT LCD NRF24L01 ���ߴ�����Գ���\r");	 	 

  NRF24L01_Init();    	//��ʼ��NRF24L01 

 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"M3S STM32");	
	LCD_ShowString(60,70,200,16,16,"NRF24L01 test");	
	LCD_ShowString(60,90,200,16,16,"www.doflye.net");
	LCD_ShowString(60,110,200,16,16,"use 2 M3S board");		  
 	while(NRF24L01_Check())	//���NRF24L01�Ƿ���λ.	
	{
		LCD_ShowString(60,130,200,16,16,"NRF24L01 Error");
		Delay_ms(200);
		LCD_Fill(60,130,239,130+16,WHITE);
 		Delay_ms(200);
	}								   
	LCD_ShowString(60,130,200,16,16,"NRF24L01 OK");	 
 	while(1)
	{
	key=KEY_Scan(0);
		if(key==KEY1)
		{
			mode=0;   
			break;
		}else if(key==KEY2)
		{
			mode=1;
			break;
		}
		t++;
		if(t==100)LCD_ShowString(10,150,230,16,16,"S1:RX_Mode  S2:TX_Mode"); //��˸��ʾ��ʾ��Ϣ
 		if(t==200)
		{	
			LCD_Fill(10,150,230,150+16,WHITE);
			t=0; 
		}
		Delay_ms(5);	  
	}   
 	LCD_Fill(10,150,240,166,WHITE);//����������ʾ		  
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ	   
	if(mode==0)//RXģʽ
	{
		LCD_ShowString(60,150,200,16,16,"NRF24L01 RX_Mode");	
		LCD_ShowString(60,170,200,16,16,"Received DATA:");	
		NRF24L01_RX_Mode();		  
		while(1)
		{	  		    		    				 
			if(NRF24L01_RxPacket(tmp_buf)==0)//һ�����յ���Ϣ,����ʾ����.
			{
				tmp_buf[32]=0;//�����ַ���������
				LCD_ShowString(0,190,239,32,16,tmp_buf);    
			}else Delay_us(100);	   
			t++;
			if(t==10000)//��Լ1s�Ӹı�һ��״̬
			{
				t=0;
				LED2_REV;
			} 				    
		};	
	}else//TXģʽ
	{							    
		LCD_ShowString(60,150,200,16,16,"NRF24L01 TX_Mode");	
		NRF24L01_TX_Mode();
		mode=' ';//�ӿո����ʼ  
		while(1)
		{	  		   				 
			if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
			{
				LCD_ShowString(60,170,239,32,16,"Sended DATA:");	
				LCD_ShowString(0,190,239,32,16,tmp_buf); 
				key=mode;
				for(t=0;t<32;t++)
				{
					key++;
					if(key>('~'))key=' ';
					tmp_buf[t]=key;	
				}
				mode++; 
				if(mode>'~')mode=' ';  	  
				tmp_buf[32]=0;//���������		   
			}else
			{										   	
 				LCD_ShowString(60,170,239,32,16,"Send Failed "); 
				LCD_Fill(0,188,240,218,WHITE);//����������ʾ			   
			};
			LED2_REV;
			Delay_ms(1500);				    
		};
	}
}

/*----------------------�·��� ������̳��www.doflye.net--------------------------*/
