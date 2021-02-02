#include "led.h"
#include "main.h"
#include "delay.h"
#include "button.h"
#include "remote.h"



#define  LED_LE_PORT   GPIOA    
#define  LED_LE_PIN    GPIO_Pin_5

#define  LED_SW_PORT   GPIOD    
#define  LED_SW_PIN    GPIO_Pin_3

#define  LED_A0_PORT   GPIOA 
#define  LED_A0_PIN    GPIO_Pin_6

#define  LED_A1_PORT   GPIOD    
#define  LED_A1_PIN    GPIO_Pin_0

#define  LED_A2_PORT   GPIOD   
#define  LED_A2_PIN    GPIO_Pin_2

#define  LED_A3_PORT   GPIOD  
#define  LED_A3_PIN    GPIO_Pin_1

void led_init(void)
{
    GPIO_Init(LED_SW_PORT, LED_SW_PIN, GPIO_Mode_In_FL_No_IT);

    GPIO_Init(LED_LE_PORT, LED_LE_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(LED_A0_PORT, LED_A0_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(LED_A1_PORT, LED_A1_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(LED_A2_PORT, LED_A2_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(LED_A3_PORT, LED_A3_PIN, GPIO_Mode_Out_PP_Low_Fast);
}

void led_on_test(void)
{
    GPIO_SetBits(LED_LE_PORT, LED_LE_PIN);
    GPIO_SetBits(LED_A0_PORT, LED_A0_PIN);
    GPIO_SetBits(LED_A1_PORT, LED_A1_PIN);
    GPIO_SetBits(LED_A2_PORT, LED_A2_PIN);
    GPIO_SetBits(LED_A3_PORT, LED_A3_PIN);
}

void led_off_test(void)
{
    GPIO_ResetBits(LED_LE_PORT, LED_LE_PIN);
    GPIO_ResetBits(LED_A0_PORT, LED_A0_PIN);
    GPIO_ResetBits(LED_A1_PORT, LED_A1_PIN);
    GPIO_ResetBits(LED_A2_PORT, LED_A2_PIN);
    GPIO_ResetBits(LED_A3_PORT, LED_A3_PIN);
}
void led_on_ctrl(u16 sta)
{
   if(sta ==0) 
     GPIO_SetBits(LED_LE_PORT, LED_LE_PIN);
   else {
   GPIO_ResetBits(LED_LE_PORT, LED_LE_PIN);
    
    if(sta & 0x01 ) {
      GPIO_ResetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_ResetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_ResetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_ResetBits(LED_A3_PORT, LED_A3_PIN);
    }
    else if(sta & 0x02){
      GPIO_SetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_ResetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_ResetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_ResetBits(LED_A3_PORT, LED_A3_PIN);
    }
    else if(sta & 0x04){
      GPIO_ResetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_SetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_ResetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_ResetBits(LED_A3_PORT, LED_A3_PIN);
    }
    else if(sta & 0x08){
      GPIO_SetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_SetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_ResetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_ResetBits(LED_A3_PORT, LED_A3_PIN);
    }
    else if(sta & 0x10){
      GPIO_ResetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_ResetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_SetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_ResetBits(LED_A3_PORT, LED_A3_PIN);
    }    
    else if(sta & 0x20){
      GPIO_SetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_ResetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_SetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_ResetBits(LED_A3_PORT, LED_A3_PIN);
    }
    else if(sta & 0x40){
      GPIO_ResetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_SetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_SetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_ResetBits(LED_A3_PORT, LED_A3_PIN);
    }
    else if(sta & 0x80 ) {
      GPIO_SetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_SetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_SetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_ResetBits(LED_A3_PORT, LED_A3_PIN);
    }
    else if(sta & 0x100){
      GPIO_ResetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_ResetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_ResetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_SetBits(LED_A3_PORT, LED_A3_PIN);
    }
    else if(sta & 0x200){
      GPIO_SetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_ResetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_ResetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_SetBits(LED_A3_PORT, LED_A3_PIN);
    }
    else if(sta & 0x400){
      GPIO_ResetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_SetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_ResetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_SetBits(LED_A3_PORT, LED_A3_PIN);
    }
    
    else if(sta & 0x800){
      GPIO_SetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_SetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_ResetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_SetBits(LED_A3_PORT, LED_A3_PIN);
    }    
    else if(sta & 0x1000){
      GPIO_ResetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_ResetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_SetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_SetBits(LED_A3_PORT, LED_A3_PIN);
    }    
    else if(sta & 0x2000){
      GPIO_SetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_ResetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_SetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_SetBits(LED_A3_PORT, LED_A3_PIN);
    }    
    else if(sta & 0x4000){
      GPIO_ResetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_SetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_SetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_SetBits(LED_A3_PORT, LED_A3_PIN);
    }
    else if(sta & 0x8000){
      GPIO_SetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_SetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_SetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_SetBits(LED_A3_PORT, LED_A3_PIN);
    }  
   }
}
void led_process(void)
{
  u16 key_sta_scan =0x00;
  Get_Key_value(&key_sta_scan);
  
  led_on_ctrl(key_sta_scan);
  nrf_send(key_sta_scan);
}

