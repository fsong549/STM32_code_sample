#include	"stm32f10x.h"
#include	"string.h"
#include	"usart.h"
#include	"delay.h"
#include	"led.h"
#include	"key.h"
#include	"24cxx.h"
#include	"ili93xx.h"
#include	"touch.h"
#include    "ucos_ii.h"  		
#include	"GUI.h"
#include	"app_cfg.h"


OS_STK Start_Task_Stk[START_TASK_STK_SIZE];		              //定义栈


/*
***************************************************************
*函数名：Load_Drive()
*功能：	 初始化硬件
*参数：	 无
*返回值：无
****************************************************************
*/
static void Load_Drive(void)
{
	u8 key;
	  /* 设置系统时钟为72M */
  Stm32_Clock_Init(9);//系统时钟设置  
  delay_init(72);	     //延时初始化
  uart_init(72,9600);			 			//初始化串口1波特率9600
  LED_Init();										//初始化LED
  KEY_Init();										//初始化按键
  AT24CXX_Init();                //初始化24C02

  GUI_Init();										//初始化uCGUI
	tp_dev.init();								//初始化触摸	
	key = KEY_Scan(0);	
	if(key==1){
		TP_Adjust();								//校准屏幕
	}
}

int main(void)
{
  Load_Drive();
  while(1) 
  {		 
		OSInit();				 //初始化操作系统
		OSTaskCreate(Start_Task,
	            (void *)0,
	   			&Start_Task_Stk[START_TASK_STK_SIZE-1],
	    		START_TASK_PRIO);  //创建开始任务

		OSStart();				//开始多任务运行
    return 0;			
  }				   
}







