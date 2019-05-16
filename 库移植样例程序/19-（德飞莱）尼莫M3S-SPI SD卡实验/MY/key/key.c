/*-------------------------------------------------------------------------------
�ļ����ƣ�key.c
�ļ����������ð�����ʼ������       
��    ע����
---------------------------------------------------------------------------------*/
#include "key.h"
#include "delay.h"
/*-------------------------------------------------------------------------------
�������ƣ�KEY_Init
�����������������ų�ʼ�����򿪶˿�ʱ�ӣ����ö˿����ţ��˿ڹ���Ƶ�ʣ��˿�����ģʽ 
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	//��PB��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//��PA��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//��PE��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	//PE2,PE3,PE4��������	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	//�˿��ٶ�
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	//�˿�ģʽ����Ϊ��������ģʽ
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	//��ʼ����Ӧ�Ķ˿�
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	//PA0��������	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	//�˿��ٶ�
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	//�˿�ģʽ����Ϊ��������ģʽ
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	//��ʼ����Ӧ�Ķ˿�
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(S1==0||S2==0||S3==0||S4==1))
	{
		Delay_ms(10);//ȥ���� 
		key_up=0;
		if(S1==0)return 1;
		else if(S2==0)return 2;
		else if(S3==0)return 3;
		else if(S4==1)return 4;
	}else if(S1==1&&S2==1&&S3==1&&S4==0)key_up=1; 	    
 	return 0;// �ް�������
}

/*----------------------�·��� ������̳��www.doflye.net--------------------------*/
