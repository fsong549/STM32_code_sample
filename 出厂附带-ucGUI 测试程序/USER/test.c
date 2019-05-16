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


OS_STK Start_Task_Stk[START_TASK_STK_SIZE];		              //����ջ


/*
***************************************************************
*��������Load_Drive()
*���ܣ�	 ��ʼ��Ӳ��
*������	 ��
*����ֵ����
****************************************************************
*/
static void Load_Drive(void)
{
	u8 key;
	  /* ����ϵͳʱ��Ϊ72M */
  Stm32_Clock_Init(9);//ϵͳʱ������  
  delay_init(72);	     //��ʱ��ʼ��
  uart_init(72,9600);			 			//��ʼ������1������9600
  LED_Init();										//��ʼ��LED
  KEY_Init();										//��ʼ������
  AT24CXX_Init();                //��ʼ��24C02

  GUI_Init();										//��ʼ��uCGUI
	tp_dev.init();								//��ʼ������	
	key = KEY_Scan(0);	
	if(key==1){
		TP_Adjust();								//У׼��Ļ
	}
}

int main(void)
{
  Load_Drive();
  while(1) 
  {		 
		OSInit();				 //��ʼ������ϵͳ
		OSTaskCreate(Start_Task,
	            (void *)0,
	   			&Start_Task_Stk[START_TASK_STK_SIZE-1],
	    		START_TASK_PRIO);  //������ʼ����

		OSStart();				//��ʼ����������
    return 0;			
  }				   
}







