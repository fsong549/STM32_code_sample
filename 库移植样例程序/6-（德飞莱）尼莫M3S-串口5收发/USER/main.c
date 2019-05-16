/*-------------------------------------------------------------------------------
文件名称：main.c
文件描述：通过串口5，使用printf函数打印信息，编译时需勾选Use MicroLIB
硬件平台：尼莫M3S开发板
编写整理：shifang
固件库  ：V3.5
技术论坛：www.doflye.net
备    注：通过简单修改可以移植到其他开发板，部分资料来源于网络。
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
	 
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);	//使能PORTC，PORTD时钟
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE); //使能UART5
 	  USART_DeInit(UART5);  //复位串口5
	  //UART5_TX   PC.12
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //PC.12
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure); //初始化PC12
   
    //UART5_RX	  PD.2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOD, &GPIO_InitStructure);  //初始化PD2    
	
	  //UART5 NVIC 配置

    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	  NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  /* USARTx configured as follow:
        - BaudRate = 9600 baud  波特率
        - Word Length = 8 Bits  数据长度
        - One Stop Bit          停止位
        - No parity             校验方式
        - Hardware flow control disabled (RTS and CTS signals) 硬件控制流
        - Receive and transmit enabled                         使能发送和接收
  */
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(UART5, &USART_InitStructure);
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//开启中断
  USART_Cmd(UART5, ENABLE);                    //使能串口 

	LED_Init();//LED初始化
  KEY_Init();//按键初始化
  SysTick_Init();//延时初始化
	BEEP_Init();   //蜂鸣器初始化
	printf("\n\rUSART Printf Example: （德飞莱）尼莫M3S开发板串口测试程序\r输入任何信息发送，接收到同样信息");
  while (1)
  {
	//使用printf函数循环发送固定信息
	Delay_ms(500);		  
  LED2_REV;	
  }
}


PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(UART5, (uint8_t) ch);

  /* 循环等待直到发送结束*/
  while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
