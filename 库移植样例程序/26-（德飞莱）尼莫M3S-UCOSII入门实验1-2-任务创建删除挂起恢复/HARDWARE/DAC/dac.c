#include "dac.h"
#include "usart.h"

void Dac_Init(void)
{
  
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //ʹ��PORTAͨ��ʱ��
   	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	  //ʹ��DACͨ��ʱ�� 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 //LED0-->PB.5 �˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4)	;//PA.4 �����
					
	DAC_InitType.DAC_Trigger=DAC_Trigger_None;	//��ʹ�ô������� TEN1=0
	DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//��ʹ�ò��η���
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//���Ρ���ֵ����
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC1�������ر� BOFF1=1

    DAC_Init(DAC_Channel_1,&DAC_InitType);
	DAC_Cmd(DAC_Channel_1, ENABLE);  //ʹ��DAC1
	DAC_DMACmd(DAC_Channel_1,DISABLE);//DAC1 DMA��ʹ��

  
    DAC_SetChannel1Data(DAC_Align_12b_R, 0);

}

//���������ѹ
//vol:0~3300,����0~3.3V
void Dac_Set_Vol(u16 vol)
{
	float temp=vol;
	temp/=1000;
	temp=temp*4096/3.3;
	DAC->DHR12R1=temp;
}





















































