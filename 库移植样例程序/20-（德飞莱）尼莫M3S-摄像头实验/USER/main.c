#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "string.h"
#include "ov7670.h"
#include "tpad.h"
#include "timer.h"
#include "exti.h"
#include "usmart.h"

const u8*LMODE_TBL[5]={"Auto","Sunny","Cloudy","Office","Home"};							//5�ֹ���ģʽ	    
const u8*EFFECTS_TBL[7]={"Normal","Negative","B&W","Redish","Greenish","Bluish","Antique"};	//7����Ч 
extern u8 ov_sta;	//��exit.c���涨��
extern u8 ov_frame;	//��timer.c���涨��	

//����LCD��ʾ
void camera_refresh(void)
{
	u32 j;
 	u16 color;	 
	if(ov_sta==2)
	{
		LCD_Scan_Dir(U2D_L2R);		//���ϵ���,������ 
		LCD_SetCursor(0x00,0x0000);	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM	
		OV7670_RRST=0;				//��ʼ��λ��ָ�� 
		OV7670_RCK=0;
		OV7670_RCK=1;
		OV7670_RCK=0;
		OV7670_RRST=1;				//��λ��ָ����� 
		OV7670_RCK=1;  
		for(j=0;j<76800;j++)
		{
			OV7670_RCK=0;
			color=GPIOC->IDR&0XFF;	//������
			OV7670_RCK=1; 
			color<<=8;  
			OV7670_RCK=0;
			color|=GPIOC->IDR&0XFF;	//������
			OV7670_RCK=1; 
			LCD->LCD_RAM=color;    
		}   							 
		EXTI_ClearITPendingBit(EXTI_Line8);  //���LINE8�ϵ��жϱ�־λ
		ov_sta=0;					//��ʼ��һ�βɼ�
 		ov_frame++; 
		LCD_Scan_Dir(DFT_SCAN_DIR);	//�ָ�Ĭ��ɨ�跽�� 
	} 
}		
 int main(void)
 {	 
	u8 key;
	u8 lightmode=0,saturation=2,brightness=2,contrast=2;
	u8 effect=0;	 
 	u8 i=0;	    
	u8 msgbuf[15];//��Ϣ������
	u8 tm=0;

	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();	
	if(lcddev.id==0X6804||lcddev.id==0X5310) 	//ǿ��������Ļ�ֱ���Ϊ320*240.��֧��3.5�����
	{
		lcddev.width=240;
		lcddev.height=320; 
	}
	KEY_Init();	 	
	TPAD_Init(72);			//����������ʼ�� 
	usmart_dev.init(72);	//��ʼ��USMART			    
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"M3S STM32");	
	LCD_ShowString(60,70,200,16,16,"OV7670 TEST");	
	LCD_ShowString(60,90,200,16,16,"www.doflye.net");
	LCD_ShowString(60,110,200,16,16,"need a 7670 camera");  
	LCD_ShowString(60,130,200,16,16,"S1:Light Mode");
	LCD_ShowString(60,150,200,16,16,"KS2:Saturation");
	LCD_ShowString(60,170,200,16,16,"S3:Brightness");
	LCD_ShowString(60,190,200,16,16,"S4:Contrast");
	LCD_ShowString(60,210,200,16,16,"TPAD(SD2):Effects");	 
  	LCD_ShowString(60,230,200,16,16,"OV7670 Init...");	  
	while(OV7670_Init())//��ʼ��OV7670
	{
		LCD_ShowString(60,230,200,16,16,"OV7670 Error!!");
		delay_ms(200);
	    LCD_Fill(60,230,239,246,WHITE);
		delay_ms(200);
	}
 	LCD_ShowString(60,230,200,16,16,"OV7670 Init OK");
	delay_ms(1500);	 	   
	OV7670_Light_Mode(lightmode);
	OV7670_Color_Saturation(saturation);
	OV7670_Brightness(brightness);
	OV7670_Contrast(contrast);
 	OV7670_Special_Effects(effect);	 
	
	TIM6_Int_Init(10000,7199);			//10Khz����Ƶ��,1�����ж�									  
	EXTI8_Init();						//ʹ�ܶ�ʱ������
	OV7670_Window_Set(10,174,240,320);	//���ô���	  
  	OV7670_CS=0;						 	 
 	while(1)
	{	
		key=KEY_Scan(0);//��֧������
		if(key)
		{
			tm=20;
			switch(key)
			{				    
				case KEY_RIGHT:	//�ƹ�ģʽLight Mode
					lightmode++;
					if(lightmode>4)lightmode=0;
					OV7670_Light_Mode(lightmode);
					sprintf((char*)msgbuf,"%s",LMODE_TBL[lightmode]);
					break;
				case KEY_DOWN:	//���Ͷ�Saturation
					saturation++;
					if(saturation>4)saturation=0;
					OV7670_Color_Saturation(saturation);
					sprintf((char*)msgbuf,"Saturation:%d",(signed char)saturation-2);
					break;
				case KEY_LEFT:	//����Brightness				 
					brightness++;
					if(brightness>4)brightness=0;
					OV7670_Brightness(brightness);
					sprintf((char*)msgbuf,"Brightness:%d",(signed char)brightness-2);
					break;
				case KEY_UP:	//�Աȶ�Contrast			    
					contrast++;
					if(contrast>4)contrast=0;
					OV7670_Contrast(contrast);
					sprintf((char*)msgbuf,"Contrast:%d",(signed char)contrast-2);
					break;
			}
		}	 
		if(TPAD_Scan(0))//��⵽�������� 
		{
			effect++;
			if(effect>6)effect=0;
			OV7670_Special_Effects(effect);//������Ч
	 		sprintf((char*)msgbuf,"%s",EFFECTS_TBL[effect]);
			tm=20;
		} 
		camera_refresh();//������ʾ
 		if(tm)
		{
			LCD_ShowString(60,60,200,16,16,msgbuf);
			tm--;
		}
		i++;
		if(i==15)//DS0��˸.
		{
			i=0;
			LED0=!LED0;
 		}
	}	   
}












