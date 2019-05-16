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

const u8*LMODE_TBL[5]={"Auto","Sunny","Cloudy","Office","Home"};							//5种光照模式	    
const u8*EFFECTS_TBL[7]={"Normal","Negative","B&W","Redish","Greenish","Bluish","Antique"};	//7种特效 
extern u8 ov_sta;	//在exit.c里面定义
extern u8 ov_frame;	//在timer.c里面定义	

//更新LCD显示
void camera_refresh(void)
{
	u32 j;
 	u16 color;	 
	if(ov_sta==2)
	{
		LCD_Scan_Dir(U2D_L2R);		//从上到下,从左到右 
		LCD_SetCursor(0x00,0x0000);	//设置光标位置 
		LCD_WriteRAM_Prepare();     //开始写入GRAM	
		OV7670_RRST=0;				//开始复位读指针 
		OV7670_RCK=0;
		OV7670_RCK=1;
		OV7670_RCK=0;
		OV7670_RRST=1;				//复位读指针结束 
		OV7670_RCK=1;  
		for(j=0;j<76800;j++)
		{
			OV7670_RCK=0;
			color=GPIOC->IDR&0XFF;	//读数据
			OV7670_RCK=1; 
			color<<=8;  
			OV7670_RCK=0;
			color|=GPIOC->IDR&0XFF;	//读数据
			OV7670_RCK=1; 
			LCD->LCD_RAM=color;    
		}   							 
		EXTI_ClearITPendingBit(EXTI_Line8);  //清除LINE8上的中断标志位
		ov_sta=0;					//开始下一次采集
 		ov_frame++; 
		LCD_Scan_Dir(DFT_SCAN_DIR);	//恢复默认扫描方向 
	} 
}		
 int main(void)
 {	 
	u8 key;
	u8 lightmode=0,saturation=2,brightness=2,contrast=2;
	u8 effect=0;	 
 	u8 i=0;	    
	u8 msgbuf[15];//消息缓存区
	u8 tm=0;

	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
 	LED_Init();			     //LED端口初始化
	LCD_Init();	
	if(lcddev.id==0X6804||lcddev.id==0X5310) 	//强制设置屏幕分辨率为320*240.以支持3.5寸大屏
	{
		lcddev.width=240;
		lcddev.height=320; 
	}
	KEY_Init();	 	
	TPAD_Init(72);			//触摸按键初始化 
	usmart_dev.init(72);	//初始化USMART			    
 	POINT_COLOR=RED;//设置字体为红色 
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
	while(OV7670_Init())//初始化OV7670
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
	
	TIM6_Int_Init(10000,7199);			//10Khz计数频率,1秒钟中断									  
	EXTI8_Init();						//使能定时器捕获
	OV7670_Window_Set(10,174,240,320);	//设置窗口	  
  	OV7670_CS=0;						 	 
 	while(1)
	{	
		key=KEY_Scan(0);//不支持连按
		if(key)
		{
			tm=20;
			switch(key)
			{				    
				case KEY_RIGHT:	//灯光模式Light Mode
					lightmode++;
					if(lightmode>4)lightmode=0;
					OV7670_Light_Mode(lightmode);
					sprintf((char*)msgbuf,"%s",LMODE_TBL[lightmode]);
					break;
				case KEY_DOWN:	//饱和度Saturation
					saturation++;
					if(saturation>4)saturation=0;
					OV7670_Color_Saturation(saturation);
					sprintf((char*)msgbuf,"Saturation:%d",(signed char)saturation-2);
					break;
				case KEY_LEFT:	//亮度Brightness				 
					brightness++;
					if(brightness>4)brightness=0;
					OV7670_Brightness(brightness);
					sprintf((char*)msgbuf,"Brightness:%d",(signed char)brightness-2);
					break;
				case KEY_UP:	//对比度Contrast			    
					contrast++;
					if(contrast>4)contrast=0;
					OV7670_Contrast(contrast);
					sprintf((char*)msgbuf,"Contrast:%d",(signed char)contrast-2);
					break;
			}
		}	 
		if(TPAD_Scan(0))//检测到触摸按键 
		{
			effect++;
			if(effect>6)effect=0;
			OV7670_Special_Effects(effect);//设置特效
	 		sprintf((char*)msgbuf,"%s",EFFECTS_TBL[effect]);
			tm=20;
		} 
		camera_refresh();//更新显示
 		if(tm)
		{
			LCD_ShowString(60,60,200,16,16,msgbuf);
			tm--;
		}
		i++;
		if(i==15)//DS0闪烁.
		{
			i=0;
			LED0=!LED0;
 		}
	}	   
}












