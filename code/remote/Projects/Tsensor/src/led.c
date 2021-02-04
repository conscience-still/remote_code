#include "led.h"
#include "main.h"
#include "delay.h"
#include "button.h"
#include "remote.h"
#include "stdbool.h"



#define  LED_LE_PORT   GPIOA    
#define  LED_LE_PIN    GPIO_Pin_5

#define  LED_E_PORT   GPIOB
#define  LED_E_PIN    GPIO_Pin_0

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
    GPIO_Init(LED_E_PORT, LED_E_PIN, GPIO_Mode_Out_PP_Low_Fast);
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
     GPIO_SetBits(LED_E_PORT, LED_E_PIN);
   else {
   GPIO_SetBits(LED_LE_PORT, LED_LE_PIN);
   GPIO_ResetBits(LED_E_PORT, LED_E_PIN);

    
    if(sta & 0x01 ) { /*1*/
      GPIO_ResetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_ResetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_ResetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_ResetBits(LED_A3_PORT, LED_A3_PIN);
    }
    else if(sta & 0x02){/*2*/
      GPIO_SetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_ResetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_ResetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_ResetBits(LED_A3_PORT, LED_A3_PIN);
    }
    else if(sta & 0x04){/*3*/
      GPIO_ResetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_SetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_ResetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_ResetBits(LED_A3_PORT, LED_A3_PIN);
    }
    else if(sta & 0x08){/*4*/
      GPIO_SetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_SetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_ResetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_ResetBits(LED_A3_PORT, LED_A3_PIN);
    }
    else if(sta & 0x10){/*5*/
      GPIO_ResetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_ResetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_SetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_ResetBits(LED_A3_PORT, LED_A3_PIN);
    }    
    else if(sta & 0x20){/*6*/
      GPIO_SetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_SetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_SetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_ResetBits(LED_A3_PORT, LED_A3_PIN);      
    }
    else if(sta & 0x40){/*7*/
      GPIO_ResetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_SetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_SetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_ResetBits(LED_A3_PORT, LED_A3_PIN);
    }
    else if(sta & 0x80 ) {/*8*/
      
      GPIO_SetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_ResetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_SetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_ResetBits(LED_A3_PORT, LED_A3_PIN);
    }
    else if(sta & 0x100){/*9*/
      GPIO_SetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_SetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_SetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_SetBits(LED_A3_PORT, LED_A3_PIN);

    }
    else if(sta & 0x200){/*10*/
      GPIO_ResetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_SetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_SetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_SetBits(LED_A3_PORT, LED_A3_PIN);      

    }
    else if(sta & 0x400){/*11*/
      GPIO_SetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_ResetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_SetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_SetBits(LED_A3_PORT, LED_A3_PIN);      
    }
    
    else if(sta & 0x800){/*12*/
      GPIO_ResetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_ResetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_SetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_SetBits(LED_A3_PORT, LED_A3_PIN);      

    }    
    else if(sta & 0x1000){/*13*/
      
      GPIO_SetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_SetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_ResetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_SetBits(LED_A3_PORT, LED_A3_PIN);
    }    
    else if(sta & 0x2000){/*14*/
      GPIO_ResetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_SetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_ResetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_SetBits(LED_A3_PORT, LED_A3_PIN);
    }    
    else if(sta & 0x4000){/*15*/
      
      GPIO_SetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_ResetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_ResetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_SetBits(LED_A3_PORT, LED_A3_PIN);
    }
    else if(sta & 0x8000){/*16*/

      GPIO_ResetBits(LED_A0_PORT, LED_A0_PIN);
      GPIO_ResetBits(LED_A1_PORT, LED_A1_PIN);
      GPIO_ResetBits(LED_A2_PORT, LED_A2_PIN);
      GPIO_SetBits(LED_A3_PORT, LED_A3_PIN);      
    }  
   }
}
u16 key_sta_scan =0x00;
u8 key_cnt = 0;
void led_process(void)
{
  
  key_sta_scan=0;
  bool sta_sw =    GPIO_ReadInputDataBit(LED_SW_PORT,LED_SW_PIN)? true :false;

  if(sta_sw)
  {
    key_cnt=0;
    Get_Key_value(&key_sta_scan);
    led_on_ctrl(key_sta_scan);
  }
  else
  {
    if(key_cnt==0)
    for(u8 i =0;i<17;i++){
      delay_ms(100);
      led_on_ctrl(key_sta_scan);
      key_sta_scan = 1<<i;
    }    
     key_cnt++;
     GPIO_SetBits(LED_E_PORT, LED_E_PIN);
  }

  nrf_send(key_sta_scan);
 
}

