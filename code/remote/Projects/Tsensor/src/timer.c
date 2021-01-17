#include "timer.h"
#include "main.h"



void GUA_Timer2_Init(void)
{
  //时钟配置
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM2,ENABLE);  
 
  //1分频，向上计数，每13us定时中断一次 
  TIM2_DeInit();
  TIM2_TimeBaseInit(TIM2_Prescaler_1, TIM2_CounterMode_Up, 16*13);     
  TIM2_ARRPreloadConfig(ENABLE);
  TIM2_ITConfig(TIM2_IT_Update , ENABLE);
  TIM2_Cmd(ENABLE);
}




