#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "ov7670.h"
 
 

//�ⲿ�ж�0�������
//��ʼ��PA0,PA13,PA15Ϊ�ж�����.
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	�����˿ڳ�ʼ��

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);

  //GPIOE.2 �ж����Լ��жϳ�ʼ������   �½��ش���
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOE.3	  �ж����Լ��жϳ�ʼ������ �½��ش���
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOE.4	  �ж����Լ��жϳ�ʼ������  �½��ش���
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


  //GPIOA.0	  �ж����Լ��жϳ�ʼ������ �����ش���
 	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

 	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
}

//�ⲿ�ж�0������� 
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY3==1)	 //����2
	{				 
		LED1=!LED1;	
	}
	EXTI_ClearITPendingBit(EXTI_Line0);  //���EXTI0��·����λ
}
 
//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY2==0)	 //����2
	{
		LED0=!LED0;	 
	}		 
	EXTI_ClearITPendingBit(EXTI_Line2);  //���EXTI0��·����λ
}
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY1==0)	 //����2
	{				 
		LED1=!LED1;	
	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);  //���EXTI0��·����λ
}

void EXTI4_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY0==0)	 //����2
	{
		LED0=!LED0;	 
	}		 
	EXTI_ClearITPendingBit(EXTI_Line4);  //���EXTI0��·����λ
}
 
 //ov_sta:0,��ʼһ֡���ݲɼ�
u8 ov_sta;
 //�ⲿ�ж�5~9�������
void EXTI9_5_IRQHandler(void)
{		 		
 
	if(EXTI_GetITStatus(EXTI_Line8)==SET)//��8�ߵ��ж�
	{     
		if(ov_sta<2)
		{
			if(ov_sta==0)
			{
				OV7670_WRST=0;	 	//��λдָ��		  		 
				OV7670_WRST=1;	
				OV7670_WREN=1;		//����д��FIFO
			}else 
			{
				OV7670_WREN=0;		//��ֹд��FIFO 
				OV7670_WRST=0;	 	//��λдָ��		  		 
				OV7670_WRST=1;	
			}
			ov_sta++;
		}
	}
 
	EXTI_ClearITPendingBit(EXTI_Line8);  //���EXTI8��·����λ						  
} 
//�ⲿ�ж�8��ʼ��
void EXTI8_Init(void)
{   
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);//PA8���ж���8
 	   	 
	EXTI_InitStructure.EXTI_Line=EXTI_Line8;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//��ռ���ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//�����ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
   
}


