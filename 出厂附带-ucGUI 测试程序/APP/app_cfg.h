#ifndef		__APP_CFG_H__
#define		__APP_CFG_H__



/*
***************************************************************
				    �궨����
****************************************************************
*/

//�����������ȼ�
#define START_TASK_PRIO                         4
#define TOUCH_TEST_TASK_PRIO                    5		  
#define UCGUI_DEMO_TASK_PRIO                    6	   	 
#define LED_TASK_PRIO                           7	


											 
//����ջ��С����λΪ OS_STK ��
#define START_TASK_STK_SIZE   					2048
#define UCGUI_DEMO_TASK_STK_SIZE   				2048
#define LED_TASK_STK_SIZE   			    	256
#define TOUCH_TEST_TASK_STK_SIZE   			   	256

/*
***************************************************************
				    �ⲿ����������
****************************************************************
*/
					// ���صĲ�������





/*
***************************************************************
				    ����������
****************************************************************
*/
void Start_Task(void *p_arg);

#endif

