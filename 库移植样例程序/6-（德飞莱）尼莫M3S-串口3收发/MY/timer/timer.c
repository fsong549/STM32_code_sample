/*-------------------------------------------------------------------------------
文件名称：timer.c
文件描述：通用定时器配置        
备    注：无
---------------------------------------------------------------------------------*/
#include "timer.h"
/*-------------------------------------------------------------------------------
程序名称：TIM2_Base_Init
程序描述：定时器TIM2通用定时功能
输入参数：定时器重装值
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void TIM2_Base_Init(u16 Count)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = Count-1;  //重装值，
	TIM_TimeBaseStructure.TIM_Prescaler =7200-1; //分频系数，72M/7200=10KHz,其他依此类推
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);     //把上述数值写入对应寄存器
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);            //使能或者失能指定的TIM中断
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;            //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);                 //把上述数值写入对应寄存

	TIM_Cmd(TIM2, ENABLE);  //使能TIMx外设
							 
}

/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
