#ifndef __RED_H
#define __RED_H 
#include "stm32f10x.h"

  
#define RDATA GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)	 //�������������

//����ң��ʶ����(ID),ÿ��ң�����ĸ�ֵ��������һ��,��Ҳ��һ����.
//����ѡ�õ�ң����ʶ����Ϊ0
#define REMOTE_ID 0      		   

extern u8 RmtCnt;	//�������µĴ���

void Remote_Init(void);    //���⴫��������ͷ���ų�ʼ��
u8 Remote_Scan(void);	     
#endif
/*----------------------�·��� ������̳��www.doflye.net--------------------------*/














