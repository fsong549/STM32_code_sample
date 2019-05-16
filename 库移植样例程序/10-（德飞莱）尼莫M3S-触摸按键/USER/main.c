/*-------------------------------------------------------------------------------
�ļ����ƣ�main.c
�ļ�������J13������ñ��SD2 ���������Ϊ�������̣�ͨ�������ı�LED2״̬
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
#include "tsensor.h"
#include "dac.h"
#include "tpad.h"   

int main(void)
{
	u8 t = 0;

	
	LED_Init();//LED��ʼ��
  KEY_Init();//������ʼ��
  SysTick_Init();//��ʱ��ʼ��
	BEEP_Init();   //��������ʼ��
  USART1_Int(9600);
	TPAD_Init();			//???????	 	 

	
  printf("\n\rADC Test: ���·�������ĪM3S������DAC1ͨ�����Գ���PA4�������\r");


      
  
  while(1)
	{					  						  		 
 		if(TPAD_Scan(0))	//???????????(?????????15ms)
		{
			LED2_REV;		//LED1??
		}
		t++;
		if(t==15)		 
		{
			t=0;
			LED3_REV;		//LED0??,????????
		}
		Delay_ms(10);
	}	

  
}

/*----------------------�·��� ������̳��www.doflye.net--------------------------*/
