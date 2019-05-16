/*-------------------------------------------------------------------------------
�ļ����ƣ�myiic.c
�ļ�������ģ��IICʱ����ƣ�
Ӳ��ƽ̨����ĪM3S������
��д����shifang
�̼���  ��V3.5
������̳��www.doflye.net
��    ע��ͨ�����޸Ŀ�����ֲ�����������壬����������Դ�����硣
---------------------------------------------------------------------------------*/
#include "myiic.h"
#include "Delay.h"
 
//��ʼ��IIC
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11); 	//PB10,PB11 �����
}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA_SET;	  	  
	IIC_SCL_SET;
	Delay_us(4);
 	IIC_SDA_CLR;//START:when CLK is high,DATA change form high to low 
	Delay_us(4);
	IIC_SCL_CLR;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL_CLR;
	IIC_SDA_CLR;//STOP:when CLK is high DATA change form low to high
 	Delay_us(4);
	IIC_SCL_SET; 
	IIC_SDA_SET;//����I2C���߽����ź�
	Delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA_SET;Delay_us(1);	   
	IIC_SCL_SET;Delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_CLR;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL_CLR;
	SDA_OUT();
	IIC_SDA_CLR;
	Delay_us(2);
	IIC_SCL_SET;
	Delay_us(2);
	IIC_SCL_CLR;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL_CLR;
	SDA_OUT();
	IIC_SDA_SET;
	Delay_us(2);
	IIC_SCL_SET;
	Delay_us(2);
	IIC_SCL_CLR;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL_CLR;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA_SET;
		else
			IIC_SDA_CLR;
		txd<<=1; 	  
		Delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL_SET;
		Delay_us(2); 
		IIC_SCL_CLR;	
		Delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL_CLR; 
        Delay_us(2);
		IIC_SCL_SET;
        receive<<=1;
        if(READ_SDA)receive++;   
		Delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}

/*----------------------�·��� ������̳��www.doflye.net--------------------------*/

























