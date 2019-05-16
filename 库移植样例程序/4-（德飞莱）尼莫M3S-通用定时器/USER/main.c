/*-------------------------------------------------------------------------------
�ļ����ƣ�main.c
�ļ���������ͨ��ʱ����LED2��˸�����250ms����ʱ������LED3��˸�����500ms��
          ��ʱ�����Ը���Ϊ������ʱ�����������ַ��滻��ʽ���¡���TIM2�滻��TIM3
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

int main(void)
{
	
	LED_Init();//LED��ʼ��
  KEY_Init();//������ʼ��
  SysTick_Init();//��ʱ��ʼ��
	TIM2_Base_Init(5000);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms  
  while(1)
	{
		Delay_ms(250);		  
		LED2_REV;		
	}
}

void TIM2_IRQHandler(void)   //TIM2�ж�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
			
		LED3_REV; //ȡ��LED3
		}
}

/*----------------------�·��� ������̳��www.doflye.net--------------------------*/
