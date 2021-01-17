#ifndef __USART_H
#define __USART_H
#include "main.h"

#define USART_MAX_RECV_LEN		255					
#define USART_RX_EN 					1						
extern u8  USART_RX_BUF[USART_MAX_RECV_LEN]; 				
extern u16 USART_RX_STA;

void NRF_RestTime(void);
void NRF_Irq(void);
void uart_init(void);
void USART_Transmit_Byte(u8 Data);
void USART_Transmit_String(u16 length,u8 *Data);
#endif /* __DELAY_H*/


