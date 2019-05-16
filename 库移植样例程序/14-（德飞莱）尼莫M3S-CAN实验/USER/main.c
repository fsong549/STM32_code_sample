/*-------------------------------------------------------------------------------
�ļ����ƣ�main.c
�ļ�������SPI CAN ���� ��������
Ӳ��ƽ̨����ĪM3S������+CAN����ģ�� 2�ף��Ӵ���������
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


int main(void)
{		
	u8 key;
	u8 i=0,t=0;
	u8 cnt=0;
	u8 canbuf[8];
	u8 res;
	u8 mode=1;//CAN����ģʽ;0,��ͨģʽ;1,����ģʽ
	
	LED_Init();//LED��ʼ��
  KEY_Init();//������ʼ��
  SysTick_Init();//��ʱ��ʼ��
	BEEP_Init();   //��������ʼ��
  USART1_Int(9600);
	LCD_Init();
  printf("\n\r���·�������ĪM3S������TFT LCD CAN mode ���Գ���\r");	 	
	CAN_Mode_Init(1,8,7,5,mode);//CAN��ʼ��,������450Kbps    

 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"M3S STM32");	
	LCD_ShowString(60,70,200,16,16,"CAN test");	
	LCD_ShowString(60,90,200,16,16,"need 2 M3S board");
	LCD_ShowString(60,110,200,16,16,"and 2 VP230 board");
	LCD_ShowString(60,130,200,16,16,"LoopBack Mode");	 
	LCD_ShowString(60,150,200,16,16,"S1:Send S2:Mode");//��ʾ��ʾ��Ϣ		
  	POINT_COLOR=BLUE;//��������Ϊ��ɫ	  
	LCD_ShowString(60,170,200,16,16,"Count:");			//��ʾ��ǰ����ֵ	
	LCD_ShowString(60,190,200,16,16,"Send Data:");		//��ʾ���͵�����	
	LCD_ShowString(60,250,200,16,16,"Receive Data:");	//��ʾ���յ�������		
 	while(1)
	{
		key=KEY_Scan(0);
	 if(key==KEY1)//S1����,����һ������
		{
			for(i=0;i<8;i++)
			{
				canbuf[i]=cnt+i;//��䷢�ͻ�����
				if(i<4)LCD_ShowxNum(60+i*32,210,canbuf[i],3,16,0X80);	//��ʾ����
				else LCD_ShowxNum(60+(i-4)*32,230,canbuf[i],3,16,0X80);	//��ʾ����
 			}
			res=Can_Send_Msg(canbuf,8);//����8���ֽ� 
			if(res)LCD_ShowString(60+80,190,200,16,16,"Failed");		//��ʾ����ʧ��
			else LCD_ShowString(60+80,190,200,16,16,"OK    ");	 		//��ʾ���ͳɹ�								   
		}
		else if(key==KEY2)//S2���£��ı�CAN�Ĺ���ģʽ
		{	   
			mode=!mode;
			CAN_Mode_Init(1,8,7,5,mode);//CAN��ͨģʽ��ʼ��,��ͨģʽ,������450Kbps
  			POINT_COLOR=RED;//��������Ϊ��ɫ 
			if(mode==0)//��ͨģʽ����Ҫ2��������
			{
				LCD_ShowString(60,130,200,16,16,"Nnormal Mode ");	    
			}else //�ػ�ģʽ,һ��������Ϳ��Բ�����.
			{
 				LCD_ShowString(60,130,200,16,16,"LoopBack Mode");
			}
 			POINT_COLOR=BLUE;//��������Ϊ��ɫ 
		}		 
		key=Can_Receive_Msg(canbuf);
		if(key)//���յ�������
		{			
			LCD_Fill(60,270,130,310,WHITE);//���֮ǰ����ʾ
 			for(i=0;i<key;i++)
			{									    
				if(i<4)LCD_ShowxNum(60+i*32,270,canbuf[i],3,16,0X80);	//��ʾ����
				else LCD_ShowxNum(60+(i-4)*32,290,canbuf[i],3,16,0X80);	//��ʾ����
 			}
		}
		t++; 
		Delay_ms(10);
		if(t==20)
		{
			LED2_REV;//��ʾϵͳ��������	
			t=0;
			cnt++;
			LCD_ShowxNum(60+48,170,cnt,3,16,0X80);	//��ʾ����
		}		   
	}
}

/*----------------------�·��� ������̳��www.doflye.net--------------------------*/
