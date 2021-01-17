#include "remote.h"
#include "main.h"
#include "stdlib.h"

#define  CS_PORT   GPIOA   
#define  CS_PIN    GPIO_Pin_5

#define  SET_PORT   GPIOA    
#define  SET_PIN    GPIO_Pin_4

typedef struct __attribute__((__packed__)){
    u16 head;                 //
    u16 self_id;                 //
    u16 net_id;                 //
    u8 nc1;               //
    u8 rf_power;          //
    u8 nc2;               //
    u8 rf_baud;          //
    u8 nc3;               //
    u8 rf_chn;          //
    u16 nc4;               //
    u8 nc5;               //
    u8 length;               //
    u8 nc6;               //
}SetSend; 
void remote_cr_init(void)
{       
  GPIO_Init(CS_PORT, CS_PIN, GPIO_Mode_Out_PP_Low_Fast);
  GPIO_Init(SET_PORT, SET_PIN, GPIO_Mode_Out_PP_Low_Fast);
  GPIO_SetBits(SET_PORT, SET_PIN);
  GPIO_ResetBits(CS_PORT, CS_PIN);
}

u8 SetNrf(void)//
{
       GPIO_ResetBits(SET_PORT, SET_PIN);
       GPIO_ResetBits(CS_PORT, CS_PIN);

      u8 *p1 = malloc(18);
      SetSend *p = (SetSend*)p1;

      p->head= 0xaa5a;
      p->self_id = 0x2233;
      p->net_id = 0x1122;
      p->rf_power = 0x00;
      p->rf_baud = 0x04;
      p->rf_chn = 0x64;
      p->length = 0x12;      
      p1[sizeof(SetSend)] = CheckSum((u8*)p, sizeof(SetSend));
      USART_Transmit_String( sizeof(SetSend)+1,p1);

#if DEBUG_DPRINT
      u8 *str = malloc(20);
      hex_str((u8*)p, sizeof(SetSend)+1, str);
      USART_Transmit_String(20,str);
//      printf("--->:%s\r\n", str);
      free(str);
#endif

      free(p1);
      return 1;
      
}

void nrf_test(void)
{
  u8 sta = 0x0A & 0x0f; 
//  for()
  USART_Transmit_String(1,&sta);
}


