#ifndef		__APP_CFG_H__
#define		__APP_CFG_H__



/*
***************************************************************
				    宏定义区
****************************************************************
*/

//设置任务优先级
#define START_TASK_PRIO                         4
#define TOUCH_TEST_TASK_PRIO                    5		  
#define UCGUI_DEMO_TASK_PRIO                    6	   	 
#define LED_TASK_PRIO                           7	


											 
//设置栈大小（单位为 OS_STK ）
#define START_TASK_STK_SIZE   					2048
#define UCGUI_DEMO_TASK_STK_SIZE   				2048
#define LED_TASK_STK_SIZE   			    	256
#define TOUCH_TEST_TASK_STK_SIZE   			   	256

/*
***************************************************************
				    外部变量声明区
****************************************************************
*/
					// 返回的操作代码





/*
***************************************************************
				    函数声明区
****************************************************************
*/
void Start_Task(void *p_arg);

#endif

