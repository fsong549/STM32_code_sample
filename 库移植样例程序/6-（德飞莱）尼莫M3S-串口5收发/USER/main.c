/*-------------------------------------------------------------------------------
�ļ����ƣ�main.c
�ļ�������ͨ������5��ʹ��printf������ӡ��Ϣ������ʱ�蹴ѡUse MicroLIB
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



#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

int main(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
	 
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);	//ʹ��PORTC��PORTDʱ��
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE); //ʹ��UART5
 	  USART_DeInit(UART5);  //��λ����5
	  //UART5_TX   PC.12
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //PC.12
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOC, &GPIO_InitStructure); //��ʼ��PC12
   
    //UART5_RX	  PD.2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOD, &GPIO_InitStructure);  //��ʼ��PD2    
	
	  //UART5 NVIC ����

    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	  NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  /* USARTx configured as follow:
        - BaudRate = 9600 baud  ������
        - Word Length = 8 Bits  ���ݳ���
        - One Stop Bit          ֹͣλ
        - No parity             У�鷽ʽ
        - Hardware flow control disabled (RTS and CTS signals) Ӳ��������
        - Receive and transmit enabled                         ʹ�ܷ��ͺͽ���
  */
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(UART5, &USART_InitStructure);
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//�����ж�
  USART_Cmd(UART5, ENABLE);                    //ʹ�ܴ��� 

	LED_Init();//LED��ʼ��
  KEY_Init();//������ʼ��
  SysTick_Init();//��ʱ��ʼ��
	BEEP_Init();   //��������ʼ��
	printf("\n\rUSART Printf Example: ���·�������ĪM3S�����崮�ڲ��Գ���\r�����κ���Ϣ���ͣ����յ�ͬ����Ϣ");
  while (1)
  {
	//ʹ��printf����ѭ�����͹̶���Ϣ
	Delay_ms(500);		  
  LED2_REV;	
  }
}


PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(UART5, (uint8_t) ch);

  /* ѭ���ȴ�ֱ�����ͽ���*/
  while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

/*----------------------�·��� ������̳��www.doflye.net--------------------------*/
