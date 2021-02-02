#include "led.h"
#include "main.h"
#include "delay.h"
#define  LED_1_PORT   GPIOD    
#define  LED_1_PIN    GPIO_Pin_0

#define  LED_2_PORT   GPIOD    
#define  LED_2_PIN    GPIO_Pin_1

#define  LED_3_PORT   GPIOD  
#define  LED_3_PIN    GPIO_Pin_2

#define  LED_4_PORT   GPIOD    
#define  LED_4_PIN    GPIO_Pin_3

#define  LED_5_PORT   GPIOB    
#define  LED_5_PIN    GPIO_Pin_0

#define  LED_6_PORT   GPIOB    
#define  LED_6_PIN    GPIO_Pin_1

#define  LED_7_PORT   GPIOB    
#define  LED_7_PIN    GPIO_Pin_2

#define  LED_8_PORT   GPIOB    
#define  LED_8_PIN    GPIO_Pin_3

#define  LED_9_PORT   GPIOB    
#define  LED_9_PIN    GPIO_Pin_4

#define  LED_10_PORT   GPIOB    
#define  LED_10_PIN    GPIO_Pin_5

#define  LED_11_PORT   GPIOB    
#define  LED_11_PIN    GPIO_Pin_6

#define  LED_12_PORT   GPIOB    
#define  LED_12_PIN    GPIO_Pin_7

#define  LED_13_PORT   GPIOD    
#define  LED_13_PIN    GPIO_Pin_4

#define  LED_14_PORT   GPIOD    
#define  LED_14_PIN    GPIO_Pin_5

#define  LED_15_PORT   GPIOD    
#define  LED_15_PIN    GPIO_Pin_6

#define  LED_16_PORT   GPIOD    
#define  LED_16_PIN    GPIO_Pin_7
void led_init(void)
{
    GPIO_Init(LED_1_PORT, LED_1_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(LED_2_PORT, LED_2_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(LED_3_PORT, LED_3_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(LED_4_PORT, LED_4_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(LED_5_PORT, LED_5_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(LED_6_PORT, LED_6_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(LED_7_PORT, LED_7_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(LED_8_PORT, LED_8_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(LED_9_PORT, LED_9_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(LED_10_PORT, LED_10_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(LED_11_PORT, LED_11_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(LED_12_PORT, LED_12_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(LED_13_PORT, LED_13_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(LED_14_PORT, LED_14_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(LED_15_PORT, LED_15_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(LED_16_PORT, LED_16_PIN, GPIO_Mode_Out_PP_Low_Fast);
}

void led_on_test(void)
{
     GPIO_SetBits(LED_1_PORT, LED_1_PIN);
    GPIO_SetBits(LED_2_PORT, LED_2_PIN);
    GPIO_SetBits(LED_3_PORT, LED_3_PIN );
    GPIO_SetBits(LED_4_PORT, LED_4_PIN);
    GPIO_SetBits(LED_5_PORT, LED_5_PIN);
    GPIO_SetBits(LED_6_PORT, LED_6_PIN);
    GPIO_SetBits(LED_7_PORT, LED_7_PIN);
    GPIO_SetBits(LED_8_PORT, LED_8_PIN);
    GPIO_SetBits(LED_9_PORT, LED_9_PIN);
    GPIO_SetBits(LED_10_PORT, LED_10_PIN);
    GPIO_SetBits(LED_11_PORT, LED_11_PIN);
    GPIO_SetBits(LED_12_PORT, LED_12_PIN);
    GPIO_SetBits(LED_13_PORT, LED_13_PIN);
    GPIO_SetBits(LED_14_PORT, LED_14_PIN);
    GPIO_SetBits(LED_15_PORT, LED_15_PIN);
    GPIO_SetBits(LED_16_PORT, LED_16_PIN);
}

void led_off_test(void)
{
    GPIO_ResetBits(LED_1_PORT, LED_1_PIN);
    GPIO_ResetBits(LED_2_PORT, LED_2_PIN);
    GPIO_ResetBits(LED_3_PORT, LED_3_PIN );
    GPIO_ResetBits(LED_4_PORT, LED_4_PIN);
    GPIO_ResetBits(LED_5_PORT, LED_5_PIN);
    GPIO_ResetBits(LED_6_PORT, LED_6_PIN);
    GPIO_ResetBits(LED_7_PORT, LED_7_PIN);
    GPIO_ResetBits(LED_8_PORT, LED_8_PIN);
    GPIO_ResetBits(LED_9_PORT, LED_9_PIN);
    GPIO_ResetBits(LED_10_PORT, LED_10_PIN);
    GPIO_ResetBits(LED_11_PORT, LED_11_PIN);
    GPIO_ResetBits(LED_12_PORT, LED_12_PIN);
    GPIO_ResetBits(LED_13_PORT, LED_13_PIN);
    GPIO_ResetBits(LED_14_PORT, LED_14_PIN);
    GPIO_ResetBits(LED_15_PORT, LED_15_PIN);
    GPIO_ResetBits(LED_16_PORT, LED_16_PIN); 
}
void led_ctrl(u8 sta)
{
//  switch(sta)
//  {
//    case 0:
//      
//      break;
//  }
  
  
  led_on_test();
  delay_ms(500);
  led_off_test();
  delay_ms(500);
  
}

