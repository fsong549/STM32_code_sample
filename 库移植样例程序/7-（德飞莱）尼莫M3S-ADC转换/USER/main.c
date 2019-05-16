/*-------------------------------------------------------------------------------
�ļ����ƣ�main.c
�ļ�������ͨ������1����ӡADC1��ѹֵ��PC1��
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

// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue;

// �ֲ����������ڱ���ת�������ĵ�ѹֵ			 
float ADC_ConvertedValueLocal;     

int main(void)
{
	LED_Init();//LED��ʼ��
  KEY_Init();//������ʼ��
  SysTick_Init();//��ʱ��ʼ��
	BEEP_Init();   //��������ʼ��
  USART1_Int(9600);
	ADC1_Init();
	
  printf("\n\rADC Test: ���·�������ĪM3S������ADCת�����Գ���\r");

  while (1)
  {
	//ʹ��printf����ѭ�����͹̶���Ϣ
  
	ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // ��ȡת����ADֵ
	
	printf("\r\n �ɼ���ֵ16���� = 0x%04X \r\n", ADC_ConvertedValue); 
	printf("\r\n ת�����ʵ�ʵ�ѹֵ = %f V \r\n",ADC_ConvertedValueLocal); 
	Delay_ms(500);		  
  LED2_REV;	
  }
}

/*----------------------�·��� ������̳��www.doflye.net--------------------------*/
