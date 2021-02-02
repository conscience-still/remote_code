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
#define T90 90.0
#define Tambient 25.0

#define ADC_RESOLUTION_12BIT 0.7277 /* (Vref+ / 4096) */

#define FACT_CALIB_ADD  ((u8 *)0x4911)
#define USER_CALIB_ADD1 ((u8 *)0x1000)
#define USER_CALIB_ADD2 ((u8 *)0x1001)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


RTC_InitTypeDef   RTC_InitStr;

/* Private function prototypes -----------------------------------------------*/
void GPIO_Initialization(void);
void ADC_Periph_Init(void);
void RTC_Periph_Init(void);
void RTC_restart(void);
void display_temp(void);
void user_calib(void);
void delay_1us(u16 n_1us);

/* Private functions ---------------------------------------------------------*/
void GPIO_Initialization(void)
{
  /* Push-button initialization */
  GPIO_Init(BUTTON_GPIO_PORT, FUNCTION_GPIO_PIN, GPIO_Mode_In_FL_IT);
  /* Led ports initialization */
  GPIO_Init(LED_GR_PORT, LED_GR_PIN, GPIO_Mode_Out_PP_High_Fast);
  GPIO_Init(LED_BL_PORT, LED_BL_PIN, GPIO_Mode_Out_PP_Low_Fast);
  /* PC0 in output push-pull low because never used by the application */
  GPIO_Init(GPIOC, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Slow);

  EXTI->CR1 = 0x00; /* PC1 (push-button) ext. interrupt to falling edge low level */
}

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

void RTC_Periph_Init(void)
{
  CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
#ifdef USE_LSE
  CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);
#else
  CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);
#endif

  /* Configures the RTC wakeup timer_step = RTCCLK/16 = LSE/16 = 488.28125 us */
  RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);
  /* Enable wake up unit Interrupt */
  RTC_ITConfig(RTC_IT_WUT, ENABLE);
  RTC_SetWakeUpCounter(100);
  RTC_WakeUpCmd(ENABLE);
  RTC_InitStr.RTC_AsynchPrediv = 0x7f;
  RTC_InitStr.RTC_SynchPrediv = 0x00ff;
  RTC_Init(&RTC_InitStr);
}

void RTC_restart(void)
{
  RTC_SetWakeUpCounter(100);
  RTC_WakeUpCmd(ENABLE);
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
//
//  GPIO_Initialization();
//  LCD_GLASS_Init();
//  ADC_Periph_Init();
//  RTC_Periph_Init();
//  enableInterrupts();
  uart_init();
button_init();
u8 a =5;
//    TOUCH_KEY_Init(0);
//led_init();
  relay_init();  
  while(1)
  {
//    i2c_read_key();
    I2C_SendData(I2C1,(u8)0xA1);

    //   a = TOUCH_KEY_Get();
//    test_init();
   printf("test :%d\r\n\n",a);
//    led_ctrl(a);
    
//    relay_ctrl(a);
//   USART_Transmit_String(1,&a);
//   GPIO_SetBits(TOUCH_I2C_CLK_PROT, TOUCH_I2C_CLK_PIN);
//   GPIO_SetBits(TOUCH_I2C_SDA_PROT, TOUCH_I2C_SDA_PIN);
//    delay_1us(100);
//   GPIO_ResetBits(TOUCH_I2C_CLK_PROT, TOUCH_I2C_CLK_PIN);
//   GPIO_ResetBits(TOUCH_I2C_SDA_PROT, TOUCH_I2C_SDA_PIN);
//       delay_1us(100);
       delay_ms(10);

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
