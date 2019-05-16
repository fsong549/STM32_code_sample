/*-------------------------------------------------------------------------------
�ļ����ƣ�main.c
�ļ�������ͨ������1����ӡ�ڲ��¶ȴ���������ֵ
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
   

int main(void)
{
	u16 adcx;
	float temp;
 	float temperate;
	
	LED_Init();//LED��ʼ��
  KEY_Init();//������ʼ��
  SysTick_Init();//��ʱ��ʼ��
	BEEP_Init();   //��������ʼ��
  USART1_Int(9600);
	T_Adc_Init();
	
  printf("\n\rADC Test: ���·�������ĪM3S������ADC�ڲ��¶�ת�����Գ���\r");


      
	while(1)
	{
		adcx=T_Get_Adc_Average(ADC_CH_TEMP,10);
		temp=(float)adcx*(3.3/4096);
		temperate=temp;//�����¶ȴ������ĵ�ѹֵ								  
		temperate=(1.43-temperate)/0.0043+25;		//�������ǰ�¶�ֵ	 
	//ʹ��printf����ѭ�����͹̶���Ϣ
  
	  printf("\r\n �ɼ���ֵ16���� = 0x%04X \r\n", adcx); 
	  printf("\r\n ת�����ʵ���¶� = %f C \r\n",temperate); 
  	Delay_ms(500);		  
    LED2_REV;	
  }
}

/*----------------------�·��� ������̳��www.doflye.net--------------------------*/
