#include "timer.h"
#include "main.h"



void GUA_Timer2_Init(void)
{
  //ʱ������
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM2,ENABLE);  
 
  //1��Ƶ�����ϼ�����ÿ13us��ʱ�ж�һ�� 
  TIM2_DeInit();
  TIM2_TimeBaseInit(TIM2_Prescaler_1, TIM2_CounterMode_Up, 16*13);     
  TIM2_ARRPreloadConfig(ENABLE);
  TIM2_ITConfig(TIM2_IT_Update , ENABLE);
  TIM2_Cmd(ENABLE);
}




