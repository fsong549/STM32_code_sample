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
  

//汉字显示 实验  

  
 int main(void)
 {	 
	u32 fontcnt;		  
	u8 i,j;
	u8 fontx[2];//gbk码
	u8 key,t;			  
 
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
 	LED_Init();			     //LED端口初始化
	LCD_Init();			  //初始化液晶 
	KEY_Init();	 		 //按键初始化
 	usmart_dev.init(72);//usmart初始化	
 	mem_init(SRAMIN);	//初始化内部内存池	

 	exfuns_init();					//为fatfs相关变量申请内存  
  	f_mount(0,fs[0]); 		 		//挂载SD卡 
 	f_mount(1,fs[1]); 				//挂载FLASH.
	key=KEY_Scan(0);				//按键扫描
	LCD_ShowString(60,50,200,16,16,"M3S STM32");
 
	while(font_init()||key==KEY_UP) //检查字库
	{
UPD:    
		LCD_Clear(WHITE);		   	//清屏
 		POINT_COLOR=RED;			//设置字体为红色	   	   	  
		LCD_ShowString(60,50,200,16,16,"M3S STM32");
		while(SD_Initialize())		//检测SD卡
		{
			LCD_ShowString(60,70,200,16,16,"SD Card Failed!");
			delay_ms(200);
			LCD_Fill(60,70,200+60,70+16,WHITE);
			delay_ms(200);		    
		}								 						    
		LCD_ShowString(60,70,200,16,16,"SD Card OK");
		LCD_ShowString(60,90,200,16,16,"Font Updating...");
		key=update_font(20,110,16,0);//从SD卡更新
		while(key)//更新失败		
		{			 		  
			LCD_ShowString(60,110,200,16,16,"Font Update Failed!");
			delay_ms(200);
			LCD_Fill(20,110,200+20,110+16,WHITE);
			delay_ms(200);		       
		} 		  
		LCD_ShowString(60,110,200,16,16,"Font Update Success!");
		delay_ms(1500);	
		LCD_Clear(WHITE);//清屏	       
	}   
	POINT_COLOR=RED;      
	Show_Str(60,50,200,16,"尼莫 M3S STM32开发板",16,0);				    	 
	Show_Str(60,70,200,16,"GBK字库测试程序",16,0);				    	 
	Show_Str(60,90,200,16,"www.doflye.net",16,0);				    	 
	Show_Str(60,110,200,16,"需要用SD卡才能更新字库",16,0);
	Show_Str(60,130,200,16,"按S1,更新字库",16,0);
 	POINT_COLOR=BLUE;  
	Show_Str(60,150,200,16,"内码高字节:",16,0);				    	 
	Show_Str(60,170,200,16,"内码低字节:",16,0);				    	 
	Show_Str(60,190,200,16,"对应汉字(16*16)为:",16,0);			 
	Show_Str(60,212,200,12,"对应汉字(12*12)为:",12,0);			 
	Show_Str(60,230,200,16,"汉字计数器:",16,0);
	LCD_Fill(60,130,200+60,130+16,WHITE);			  
	while(1)
	{
		fontcnt=0;
		for(i=0x81;i<0xff;i++)
		{		
			fontx[0]=i;
			LCD_ShowNum(148,150,i,3,16);//显示内码高字节    
			for(j=0x40;j<0xfe;j++)
			{
				if(j==0x7f)continue;
				fontcnt++;
				LCD_ShowNum(148,170,j,3,16);//显示内码低字节	 
				LCD_ShowNum(148,230,fontcnt,5,16);//显示内码低字节	 
			 	fontx[1]=j;
				Show_Font(204,190,fontx,16,0);	  
				Show_Font(168,212,fontx,12,0);	  		 		 
				t=200;
				while(t--)//延时,同时扫描按键
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


