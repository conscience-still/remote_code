#include "relay.h"
#include "main.h"
#include "delay.h"
#define  REALY_1_PORT   GPIOB    
#define  REALY_1_PIN    GPIO_Pin_3

#define  REALY_2_PORT   GPIOB    
#define  REALY_2_PIN    GPIO_Pin_2

#define  REALY_3_PORT   GPIOB  
#define  REALY_3_PIN    GPIO_Pin_1

#define  REALY_4_PORT   GPIOC    
#define  REALY_4_PIN    GPIO_Pin_6

#define  REALY_5_PORT   GPIOC    
#define  REALY_5_PIN    GPIO_Pin_5

#define  REALY_6_PORT   GPIOC    
#define  REALY_6_PIN    GPIO_Pin_4

#define  REALY_7_PORT   GPIOC    
#define  REALY_7_PIN    GPIO_Pin_3

#define  REALY_8_PORT   GPIOC   
#define  REALY_8_PIN    GPIO_Pin_2

#define  REALY_9_PORT   GPIOD   
#define  REALY_9_PIN    GPIO_Pin_7

#define  REALY_10_PORT   GPIOD    
#define  REALY_10_PIN    GPIO_Pin_6

#define  REALY_11_PORT   GPIOD    
#define  REALY_11_PIN    GPIO_Pin_5

#define  REALY_12_PORT   GPIOD    
#define  REALY_12_PIN    GPIO_Pin_4

#define  REALY_13_PORT   GPIOB    
#define  REALY_13_PIN    GPIO_Pin_7

#define  REALY_14_PORT   GPIOB    
#define  REALY_14_PIN    GPIO_Pin_6

#define  REALY_15_PORT   GPIOB   
#define  REALY_15_PIN    GPIO_Pin_5

#define  REALY_16_PORT   GPIOB   
#define  REALY_16_PIN    GPIO_Pin_4
void relay_init(void)
{
    GPIO_Init(REALY_1_PORT, REALY_1_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(REALY_2_PORT, REALY_2_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(REALY_3_PORT, REALY_3_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(REALY_4_PORT, REALY_4_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(REALY_5_PORT, REALY_5_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(REALY_6_PORT, REALY_6_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(REALY_7_PORT, REALY_7_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(REALY_8_PORT, REALY_8_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(REALY_9_PORT, REALY_9_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(REALY_10_PORT, REALY_10_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(REALY_11_PORT, REALY_11_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(REALY_12_PORT, REALY_12_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(REALY_13_PORT, REALY_13_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(REALY_14_PORT, REALY_14_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(REALY_15_PORT, REALY_15_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(REALY_16_PORT, REALY_16_PIN, GPIO_Mode_Out_PP_Low_Fast);
}

void relay_on(void)
{
    GPIO_SetBits(REALY_1_PORT, REALY_1_PIN);
    GPIO_SetBits(REALY_2_PORT, REALY_2_PIN);
    GPIO_SetBits(REALY_3_PORT, REALY_3_PIN );
    GPIO_SetBits(REALY_4_PORT, REALY_4_PIN);
    GPIO_SetBits(REALY_5_PORT, REALY_5_PIN);
    GPIO_SetBits(REALY_6_PORT, REALY_6_PIN);
    GPIO_SetBits(REALY_7_PORT, REALY_7_PIN);
    GPIO_SetBits(REALY_8_PORT, REALY_8_PIN);
    GPIO_SetBits(REALY_9_PORT, REALY_9_PIN);
    GPIO_SetBits(REALY_10_PORT, REALY_10_PIN);
    GPIO_SetBits(REALY_11_PORT, REALY_11_PIN);
    GPIO_SetBits(REALY_12_PORT, REALY_12_PIN);
    GPIO_SetBits(REALY_13_PORT, REALY_13_PIN);
    GPIO_SetBits(REALY_14_PORT, REALY_14_PIN);
    GPIO_SetBits(REALY_15_PORT, REALY_15_PIN);
    GPIO_SetBits(REALY_16_PORT, REALY_16_PIN);
}

void relay_off(void)
{
    GPIO_ResetBits(REALY_1_PORT, REALY_1_PIN);
    GPIO_ResetBits(REALY_2_PORT, REALY_2_PIN);
    GPIO_ResetBits(REALY_3_PORT, REALY_3_PIN );
    GPIO_ResetBits(REALY_4_PORT, REALY_4_PIN);
    GPIO_ResetBits(REALY_5_PORT, REALY_5_PIN);
    GPIO_ResetBits(REALY_6_PORT, REALY_6_PIN);
    GPIO_ResetBits(REALY_7_PORT, REALY_7_PIN);
    GPIO_ResetBits(REALY_8_PORT, REALY_8_PIN);
    GPIO_ResetBits(REALY_9_PORT, REALY_9_PIN);
    GPIO_ResetBits(REALY_10_PORT, REALY_10_PIN);
    GPIO_ResetBits(REALY_11_PORT, REALY_11_PIN);
    GPIO_ResetBits(REALY_12_PORT, REALY_12_PIN);
    GPIO_ResetBits(REALY_13_PORT, REALY_13_PIN);
    GPIO_ResetBits(REALY_14_PORT, REALY_14_PIN);
    GPIO_ResetBits(REALY_15_PORT, REALY_15_PIN);
    GPIO_ResetBits(REALY_16_PORT, REALY_16_PIN); 
}
void relay_ctrl(u16 sta)
{ 
//  relay_on();
//  delay_ms(100);
//  delay_ms(100);
    if(sta == 0)
      return;
    relay_off();

    if(sta & 0x01 ) {
      GPIO_SetBits(REALY_1_PORT, REALY_1_PIN);
    }
    else if(sta & 0x02){
      GPIO_SetBits(REALY_2_PORT, REALY_2_PIN);
    }
    else if(sta & 0x04){
      GPIO_SetBits(REALY_3_PORT, REALY_3_PIN);
    }
    else if(sta & 0x08){
      GPIO_SetBits(REALY_4_PORT, REALY_4_PIN );
    }
    else if(sta & 0x10){
      GPIO_SetBits(REALY_5_PORT, REALY_5_PIN );
    }    
    else if(sta & 0x20){
    GPIO_SetBits(REALY_6_PORT, REALY_6_PIN);
    }
    else if(sta & 0x40){
    GPIO_SetBits(REALY_7_PORT, REALY_7_PIN);
    }
    else if(sta & 0x80 ) {
    GPIO_SetBits(REALY_8_PORT, REALY_8_PIN);
    }
    else if(sta & 0x100){
    GPIO_SetBits(REALY_9_PORT, REALY_9_PIN);
    }
    else if(sta & 0x200){
    GPIO_SetBits(REALY_10_PORT, REALY_10_PIN);
    }
    else if(sta & 0x400){
    GPIO_SetBits(REALY_11_PORT, REALY_11_PIN);
    }
    
    else if(sta & 0x800){
    GPIO_SetBits(REALY_12_PORT, REALY_12_PIN);
    }    
    else if(sta & 0x1000){
    GPIO_SetBits(REALY_13_PORT, REALY_13_PIN);
    }    
    else if(sta & 0x2000){
    GPIO_SetBits(REALY_14_PORT, REALY_14_PIN); 

    }    
    else if(sta & 0x4000){
    GPIO_SetBits(REALY_15_PORT, REALY_15_PIN);

    }
    else if(sta & 0x8000){
    GPIO_SetBits(REALY_16_PORT, REALY_16_PIN); 

    }    
}

