/** 
  ******************************************************************************
  * @file    main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    29-Oct-2012
  * @brief   Main program body.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */



/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "main.h"
#include "stm8l_discovery_lcd.h"
#include <math.h>
#include "usart.h"
#include "stdio.h"
#include "i2c_touch_bs8116.h"
#include "led.h"
#include "relay.h"
/**
  * @addtogroup LCD_Example1
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

//#define ADVANCED_MODE


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


RTC_InitTypeDef   RTC_InitStr;

/* Private function prototypes -----------------------------------------------*/

void delay_1us(u16 n_1us);

/* Private functions ---------------------------------------------------------*/

void ADC_Periph_Init(void)
{
  u8 idx;
  CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);
  ADC1->CR1 |= 0x01; //ADON
  ADC1->TRIGR[0] = 0x20; //TSON
  for (idx = 0;idx < 50;idx++);
  ADC_Init(ADC1, ADC_ConversionMode_Single,
           ADC_Resolution_12Bit, ADC_Prescaler_1);
  ADC_SamplingTimeConfig(ADC1, ADC_Group_FastChannels, ADC_SamplingTime_192Cycles);
  ADC_ChannelCmd(ADC1, ADC_Channel_TempSensor, ENABLE);
  ADC1->SQR[0] |= 0x80; //DMA disable
}




/**
  * @brief main entry point.
  * @par Parameters:
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  */
void main(void)
{


  CLK->CKDIVR = 0x00; // Fcpu = 16MHz
  uart_init();
//  button_init();
//  led_init();
//  remote_cr_init();
//  relay_init();  
  while(1)
  {
//    led_process();
//   printf("test \r\n\n");    
//    relay_ctrl(a);

       delay_ms(500);
USART1->DR = 0x01;
//  if(USART_GetFlagStatus(USART1,USART_IT_RXNE))
//  {
////    USART1->DR
//    USART_Transmit_String(10,a);
//    USART_ClearFlag(USART1,USART_IT_RXNE);
//  } 
//    if(USART_GetFlagStatus(USART1,USART_IT_IDLE))
//    {
//          USART_Transmit_String(10,a);
//    USART_ClearFlag(USART1,USART_IT_IDLE);
//    }
  
  }
}
#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

/**
  * @}
  */

/******************* (C) COPYRIGHT 1009 STMicroelectronics *****END OF FILE****/
