#ifndef __MYIIC_H
#define __MYIIC_H
#include "stm32f10x.h"
/*-------------------------------------------------------------------------------
�ļ����ƣ�myiic.c
�ļ�������ģ��IICʱ����ƣ�
Ӳ��ƽ̨����ĪM3S������
��д����shifang
�̼���  ��V3.5
������̳��www.doflye.net
��    ע��ͨ�����޸Ŀ�����ֲ�����������壬����������Դ�����硣
---------------------------------------------------------------------------------*/

//IO��������
#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}

//IO��������	 
#define IIC_SCL_SET GPIO_SetBits(GPIOB,GPIO_Pin_10)
#define IIC_SCL_CLR GPIO_ResetBits(GPIOB,GPIO_Pin_10)
#define IIC_SDA_SET GPIO_SetBits(GPIOB,GPIO_Pin_11)
#define IIC_SDA_CLR GPIO_ResetBits(GPIOB,GPIO_Pin_11) 
#define READ_SDA   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) //����SDA 

//IIC���в�������


void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif

/*----------------------�·��� ������̳��www.doflye.net--------------------------*/














