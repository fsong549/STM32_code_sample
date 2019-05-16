/*-------------------------------------------------------------------------------
�ļ����ƣ�timer.c
�ļ�������ͨ�ö�ʱ������        
��    ע����
---------------------------------------------------------------------------------*/
#include "timer.h"
/*-------------------------------------------------------------------------------
�������ƣ�TIM2_Base_Init
������������ʱ��TIM2ͨ�ö�ʱ����
�����������ʱ����װֵ
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void TIM2_Base_Init(u16 Count)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = Count-1;  //��װֵ��
	TIM_TimeBaseStructure.TIM_Prescaler =7200-1; //��Ƶϵ����72M/7200=10KHz,������������
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);     //��������ֵд���Ӧ�Ĵ���
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);            //ʹ�ܻ���ʧ��ָ����TIM�ж�
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;            //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);                 //��������ֵд���Ӧ�Ĵ�

	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx����
							 
}

/*----------------------�·��� ������̳��www.doflye.net--------------------------*/
