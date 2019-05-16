#include	"app_cfg.h"
#include    "ucos_ii.h"  
#include    "led.h"
#include    "gui.h"

/*
***************************************************************
					ȫ�ֱ�����
****************************************************************
*/
/********************ϵͳ��ջ**********************************/
OS_STK UCGUI_DEMO_Task_Stk[UCGUI_DEMO_TASK_STK_SIZE];		         //����ջ
OS_STK LED_Task_Stk[LED_TASK_STK_SIZE];		         				//����ջ
OS_STK TOUCH_TEST_Task_Stk[TOUCH_TEST_TASK_STK_SIZE];		         //����ջ
/*
***************************************************************
					����������
****************************************************************
*/

static void Create_Task(void);
void Start_Task(void *p_arg);
static void UCGUI_DEMO_Task(void *p_arg);
static void LED_Task(void *p_arg);
static void TOUCH_TEST_Task(void *p_arg);



/*
***************************************************************
*��������Create_Task()
*���ܣ�	 ��������
*������	 ��
*����ֵ����
****************************************************************
*/
static void Create_Task(void)
{	   
	 
	OSTaskCreateExt(UCGUI_DEMO_Task,
				   (void *)0,
					&UCGUI_DEMO_Task_Stk[UCGUI_DEMO_TASK_STK_SIZE -1],
	 				UCGUI_DEMO_TASK_PRIO,UCGUI_DEMO_TASK_PRIO,
	   				& UCGUI_DEMO_Task_Stk[0],
	   				UCGUI_DEMO_TASK_STK_SIZE,
	   				(void *)0,
	   				OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR );	   	//����UCGUI DEMO����
	OSTaskCreateExt(LED_Task,
				   (void *)0,
					&LED_Task_Stk[LED_TASK_STK_SIZE -1],
	 				LED_TASK_PRIO,LED_TASK_PRIO,
	   				& LED_Task_Stk[0],
	   				LED_TASK_STK_SIZE,
	   				(void *)0,
	   				OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR );	   	
	OSTaskCreateExt(TOUCH_TEST_Task,
				   (void *)0,
					&TOUCH_TEST_Task_Stk[TOUCH_TEST_TASK_STK_SIZE -1],
	 				TOUCH_TEST_TASK_PRIO,TOUCH_TEST_TASK_PRIO,
	   				& TOUCH_TEST_Task_Stk[0],
	   				TOUCH_TEST_TASK_STK_SIZE,
	   				(void *)0,
	   				OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR );																  	
}


/*
***************************************************************
*��������Start_Task
*���ܣ�	 ��ʼ����
*������	 p_arg
*����ֵ����
****************************************************************
*/
void Start_Task(void *p_arg)
{
    (void)p_arg;                		// 'p_arg' ��û���õ�����ֹ��������ʾ����


	Create_Task();						//��������
    while (1)
    {
       OSTimeDlyHMSM(0, 0, 0, 500);	 
    }

}

/*
***************************************************************
*��������GUI_DEMO_Task
*���ܣ�	 ����uCGUI��DEMO
*������	 p_arg
*����ֵ����
****************************************************************
*/
static void UCGUI_DEMO_Task(void *p_arg)
{
	(void)p_arg;
	
	while(1)
	{
		 GUIDEMO_main();
     OSTimeDlyHMSM(0, 0, 0, 10);	 	 	 
	}	
}


/*
***************************************************************
*��������LED_Task
*���ܣ�	 LED��ش�������
*������	 p_arg
*����ֵ����
****************************************************************
*/
static void LED_Task(void *p_arg)
{
	(void)p_arg;
	
	while(1)
	{
		 LED0 = 0;
		 LED1 = 1;
		 OSTimeDlyHMSM(0, 0, 0, 200);	
		 LED0 = 1;
		 LED1 = 0;
		 OSTimeDlyHMSM(0, 0, 0, 200);		  
	}	
}

/*
***************************************************************
*��������TOUCH_TEST_Task
*���ܣ�	 �����������
*������	 p_arg
*����ֵ����
****************************************************************
*/
static void TOUCH_TEST_Task(void *p_arg)
{
	(void)p_arg;
	
	while(1)
	{
		 GUI_TOUCH_Exec();			 //���Ӻ�ˢ�´�����
		 OSTimeDlyHMSM(0, 0, 0, 10);		  
	}	
}







