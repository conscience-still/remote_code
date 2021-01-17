#include "stm8l15x.h"
#include "main.h"
#include "usart.h"
#include "stdio.h"

#define USART_TX_PORT  GPIOA
#define USART_RX_PORT  GPIOA

#define USART_TX_PINS  GPIO_Pin_2
#define USART_RX_PINS  GPIO_Pin_3


void uart_gpio_init()
{
    GPIO_Init(USART_TX_PORT,USART_TX_PINS, GPIO_Mode_Out_PP_Low_Fast);

    GPIO_Init(USART_RX_PORT,USART_RX_PINS, GPIO_Mode_In_PU_No_IT);
}

void uart_init(void)
{
//    uart_gpio_init();   

    CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);

    //remapping
    SYSCFG_REMAPPinConfig(REMAP_Pin_USART1TxRxPortA,ENABLE);

    USART_DeInit(USART1);

    /* UART1 configuration ------------------------------------------------------*/
    /* UART1 configured as follow:
        - USARTx = 1
        - BaudRate = 9600baud  
        - USART_WordLength = 8 Bits
        - One Stop Bit
        - No parity
        - Receive and transmit enabled
    */
    USART_Init(USART1, (uint32_t)115200, USART_WordLength_8b, USART_StopBits_1, USART_Parity_No, (USART_Mode_TypeDef)(USART_Mode_Tx | USART_Mode_Rx));

    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART1, ENABLE);
      asm("rim");
  __enable_interrupt();//中断使能   
}

void USART_Transmit_Byte(u8 Data)
{
   USART1->DR = Data;
   while(!(USART1->SR&USART_SR_TXE));
}
void USART_Transmit_String(u16 length,u8 *Data)
{
  while(length)
  {
    length--;
    USART_Transmit_Byte(*Data);
    Data++;
  }
}


int fputc(int ch) ////发送一个字符协议
{
    USART1->DR = ch;
    while(!(USART1->SR&USART_SR_TXE));

    return ch;
}
/*************************************************************/
u8  USART_RX_BUF[USART_MAX_RECV_LEN];
u16 USART_RX_STA=0;

u8 NRF_RecvdData(void)
{
	u8 ret = 0;
	if((USART_RX_STA&(1<<15)) != 0)
		ret = 1;
	return ret;
}
u16 NRF_RcvLen(void)
{
	return (USART_RX_STA & 0x7FFF);
}
u8* NRF_RcvBuff(void)
{
	return USART_RX_BUF;
}

void NRF_ClsRecvd(void)
{
	USART_RX_STA = 0;
}


typedef struct  __attribute__((__packed__))
{
  u32 stat    :1;
  u32 timOut  :1;
  u32 cunt    :15;
  u32 des     :15;
}TboxTimTypeDef;
TboxTimTypeDef gNRFTimeManage;
#define TON   (1)
#define TOFF  (0)

void TimerManageInit(TboxTimTypeDef *t,u8 stat,u16 destim)
{
  t->des  = destim;
  t->stat = stat;
  t->cunt = 0;
  t->timOut = 0;
}
void NRF_RestTime(void)
{
      if(gNRFTimeManage.stat == TON)
      {
              (gNRFTimeManage.cunt < gNRFTimeManage.des)?(gNRFTimeManage.cunt++):\
                      (TimerManageInit(&gNRFTimeManage,TOFF,0),USART_RX_STA |=1<<15);
      }	
}

void NRF_Irq(void)
{
  	u8 res;	      
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{	 
		res =USART_ReceiveData8(USART1);
    #if 0
		USART_SendData8(USART1,res);
		#endif

      
                if((USART_RX_STA & ~(1<<15))<USART_MAX_RECV_LEN)
                {
                      TimerManageInit(&gNRFTimeManage,TON,5);
                      USART_RX_BUF[USART_RX_STA++]=res;		 
                }else 
                {
                        USART_RX_STA|=1<<15;				
                } 
          }
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}

void Parse_NRF(void){
  
  if(NRF_RecvdData())
  {
    if(NRF_RcvLen()>1)
    {
      u16 len = NRF_RcvLen(); 
      u8 *p = NRF_RcvBuff();
      
    }
  }
}


