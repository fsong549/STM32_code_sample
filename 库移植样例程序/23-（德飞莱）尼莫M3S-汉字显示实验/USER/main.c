#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "flash.h"
#include "usart.h"	  
#include "sram.h"
#include "malloc.h"
#include "string.h"
#include "mmc_sd.h"
#include "ff.h"
#include "exfuns.h"
#include "usmart.h"
#include "fontupd.h"
#include "text.h"
  

//������ʾ ʵ��  

  
 int main(void)
 {	 
	u32 fontcnt;		  
	u8 i,j;
	u8 fontx[2];//gbk��
	u8 key,t;			  
 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();			  //��ʼ��Һ�� 
	KEY_Init();	 		 //������ʼ��
 	usmart_dev.init(72);//usmart��ʼ��	
 	mem_init(SRAMIN);	//��ʼ���ڲ��ڴ��	

 	exfuns_init();					//Ϊfatfs��ر��������ڴ�  
  	f_mount(0,fs[0]); 		 		//����SD�� 
 	f_mount(1,fs[1]); 				//����FLASH.
	key=KEY_Scan(0);				//����ɨ��
	LCD_ShowString(60,50,200,16,16,"M3S STM32");
 
	while(font_init()||key==KEY_UP) //����ֿ�
	{
UPD:    
		LCD_Clear(WHITE);		   	//����
 		POINT_COLOR=RED;			//��������Ϊ��ɫ	   	   	  
		LCD_ShowString(60,50,200,16,16,"M3S STM32");
		while(SD_Initialize())		//���SD��
		{
			LCD_ShowString(60,70,200,16,16,"SD Card Failed!");
			delay_ms(200);
			LCD_Fill(60,70,200+60,70+16,WHITE);
			delay_ms(200);		    
		}								 						    
		LCD_ShowString(60,70,200,16,16,"SD Card OK");
		LCD_ShowString(60,90,200,16,16,"Font Updating...");
		key=update_font(20,110,16,0);//��SD������
		while(key)//����ʧ��		
		{			 		  
			LCD_ShowString(60,110,200,16,16,"Font Update Failed!");
			delay_ms(200);
			LCD_Fill(20,110,200+20,110+16,WHITE);
			delay_ms(200);		       
		} 		  
		LCD_ShowString(60,110,200,16,16,"Font Update Success!");
		delay_ms(1500);	
		LCD_Clear(WHITE);//����	       
	}   
	POINT_COLOR=RED;      
	Show_Str(60,50,200,16,"��Ī M3S STM32������",16,0);				    	 
	Show_Str(60,70,200,16,"GBK�ֿ���Գ���",16,0);				    	 
	Show_Str(60,90,200,16,"www.doflye.net",16,0);				    	 
	Show_Str(60,110,200,16,"��Ҫ��SD�����ܸ����ֿ�",16,0);
	Show_Str(60,130,200,16,"��S1,�����ֿ�",16,0);
 	POINT_COLOR=BLUE;  
	Show_Str(60,150,200,16,"������ֽ�:",16,0);				    	 
	Show_Str(60,170,200,16,"������ֽ�:",16,0);				    	 
	Show_Str(60,190,200,16,"��Ӧ����(16*16)Ϊ:",16,0);			 
	Show_Str(60,212,200,12,"��Ӧ����(12*12)Ϊ:",12,0);			 
	Show_Str(60,230,200,16,"���ּ�����:",16,0);
	LCD_Fill(60,130,200+60,130+16,WHITE);			  
	while(1)
	{
		fontcnt=0;
		for(i=0x81;i<0xff;i++)
		{		
			fontx[0]=i;
			LCD_ShowNum(148,150,i,3,16);//��ʾ������ֽ�    
			for(j=0x40;j<0xfe;j++)
			{
				if(j==0x7f)continue;
				fontcnt++;
				LCD_ShowNum(148,170,j,3,16);//��ʾ������ֽ�	 
				LCD_ShowNum(148,230,fontcnt,5,16);//��ʾ������ֽ�	 
			 	fontx[1]=j;
				Show_Font(204,190,fontx,16,0);	  
				Show_Font(168,212,fontx,12,0);	  		 		 
				t=200;
				while(t--)//��ʱ,ͬʱɨ�谴��
				{
					delay_ms(1);
					key=KEY_Scan(0);
					if(key==KEY_UP)goto UPD;
				}
				LED0=!LED0;
			}   
		}	
	} 
}


