/*-------------------------------------------------------------------------------
�ļ����ƣ�main.c
�ļ��������ı�DAC1ͨ����ֵ����Ӧ������PA4�������ñ����ʾ����������ѹֵ
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
   

int main(void)
{
	u16 dac_temp = 0;

	
	LED_Init();//LED��ʼ��
  KEY_Init();//������ʼ��
  SysTick_Init();//��ʱ��ʼ��
	BEEP_Init();   //��������ʼ��
  USART1_Int(9600);
	DAC1_Init();  //�ػ�ģʽ��ʼ��		 	 

	
  printf("\n\rADC Test: ���·�������ĪM3S������DAC1ͨ�����Գ���PA4�������\r");


      
	while(1)
	{
		DAC1_Set_Vol(dac_temp);
		dac_temp += 50;
		if(dac_temp == 4096)
			 dac_temp = 0;
  	Delay_ms(500);		  
    LED2_REV;	
  }
}

/*----------------------�·��� ������̳��www.doflye.net--------------------------*/
