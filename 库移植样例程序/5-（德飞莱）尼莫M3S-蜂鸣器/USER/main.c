/*-------------------------------------------------------------------------------
�ļ����ƣ�main.c
�ļ���������ͨ��ʱ����LED2��˸�����250ms����ʱ�����Ʒ�������LED3
Ӳ��ƽ̨����ĪM3S������
��д����shifang
�̼���  ��V3.5
������̳��www.doflye.net
��    ע��ͨ�����޸Ŀ�����ֲ�����������壬����������Դ�����硣
---------------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "timer.h"
#include "beep.h"

uint8_t BeepFlag=1;

int main(void)
{
	
	LED_Init();//LED��ʼ��
  KEY_Init();//������ʼ��
  SysTick_Init();//��ʱ��ʼ��
	BEEP_Init();   //��������ʼ��
	TIM2_Base_Init(1000);//10Khz�ļ���Ƶ�ʣ�������1000Ϊ100ms  
  while(1)
	{
		Delay_ms(250);		  
		LED2_REV;		
	}
}

void TIM2_IRQHandler(void)   //TIM2�ж�
{ 
	static uint8_t i;
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		if(BeepFlag)	
		   BEEP_REV; //ȡ��������
		else
			 BEEP_OFF;
		i++;
		if(i==20)
		{
			BeepFlag=!BeepFlag;
			LED3_REV;
			i=0;
		}
		}
}

/*----------------------�·��� ������̳��www.doflye.net--------------------------*/
