#include	"app_cfg.h"
#include    "ucos_ii.h"  
#include    "led.h"
#include    "gui.h"

/*
***************************************************************
					全局变量区
****************************************************************
*/
/********************系统堆栈**********************************/
OS_STK UCGUI_DEMO_Task_Stk[UCGUI_DEMO_TASK_STK_SIZE];		         //定义栈
OS_STK LED_Task_Stk[LED_TASK_STK_SIZE];		         				//定义栈
OS_STK TOUCH_TEST_Task_Stk[TOUCH_TEST_TASK_STK_SIZE];		         //定义栈
/*
***************************************************************
					函数声明区
****************************************************************
*/

static void Create_Task(void);
void Start_Task(void *p_arg);
static void UCGUI_DEMO_Task(void *p_arg);
static void LED_Task(void *p_arg);
static void TOUCH_TEST_Task(void *p_arg);



/*
***************************************************************
*函数名：Create_Task()
*功能：	 创建任务
*参数：	 无
*返回值：无
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
	   				OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR );	   	//创建UCGUI DEMO任务
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
*函数名：Start_Task
*功能：	 开始任务
*参数：	 p_arg
*返回值：无
****************************************************************
*/
void Start_Task(void *p_arg)
{
    (void)p_arg;                		// 'p_arg' 并没有用到，防止编译器提示警告


	Create_Task();						//创建任务
    while (1)
    {
       OSTimeDlyHMSM(0, 0, 0, 500);	 
    }

}

/*
***************************************************************
*函数名：GUI_DEMO_Task
*功能：	 运行uCGUI的DEMO
*参数：	 p_arg
*返回值：无
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
*函数名：LED_Task
*功能：	 LED监控代码运行
*参数：	 p_arg
*返回值：无
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
*函数名：TOUCH_TEST_Task
*功能：	 触摸检测任务
*参数：	 p_arg
*返回值：无
****************************************************************
*/
static void TOUCH_TEST_Task(void *p_arg)
{
	(void)p_arg;
	
	while(1)
	{
		 GUI_TOUCH_Exec();			 //监视和刷新触摸板
		 OSTimeDlyHMSM(0, 0, 0, 10);		  
	}	
}







