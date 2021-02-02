/*********************************************************************************************************//**
 * @file    i2c_touch_bs8116.c
 * @version V1.00
 * @date    06/24/2016
 * @brief   This file contains oled algorithm.
 ************************************************************************************************************/
/* Includes ------------------------------------------------------------------------------------------------*/
#include <string.h>
#include "i2c_touch_bs8116.h"
#include "delay.h"
/* Private typedef -----------------------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------------------------------------*/
const u16 keycode[12] = {0x0800, 0x0010, 0x0004, 0x0001,
												 0x0040, 0x0100, 0x0400, 0x0002,
												 0x0020, 0x0080, 0x0008, 0x0200};
//0-K12, 1-K5, 2-K3, 3-K1, 4-K7, 5-K9, 6-K11, 7-K2, 8-K6, 9-K8, *-K4, #-K10
                              
/* Private macro -------------------------------------------------------------------------------------------*/




#define TOUCH_I2C_CLK_HIGH()    ( GPIO_SetBits(TOUCH_I2C_CLK_PROT, TOUCH_I2C_CLK_PIN))
#define TOUCH_I2C_CLK_LOW()     (GPIO_ResetBits(TOUCH_I2C_CLK_PROT, TOUCH_I2C_CLK_PIN))
#define TOUCH_I2C_SDA_HIGH()    (GPIO_SetBits(TOUCH_I2C_SDA_PROT, TOUCH_I2C_SDA_PIN))
#define TOUCH_I2C_SDA_LOW()     (GPIO_ResetBits(TOUCH_I2C_SDA_PROT, TOUCH_I2C_SDA_PIN))
                              
#define READ_SCL               TOUCH_I2C_CLK_PROT->IDR  & TOUCH_I2C_CLK_PIN   //  STM_PininGetState(TOUCH_I2C_SCL_IN)
#define READ_SDA               TOUCH_I2C_SDA_PROT->IDR  & TOUCH_I2C_SDA_PIN //     STM_PininGetState(TOUCH_I2C_SDA_IN)                              
                              
#define delayXuS(x)   		delay_1us(x);//			BOARD_DelayXuS(x)

                                              
/* Global variables ----------------------------------------------------------------------------------------*/
//TOUCH_Typedef gTouch;
/* Private variables ---------------------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------------------------------------*/
u8 I2C_BS8112aInit(u8* p);
u8 I2C_Start(void);
void I2C_Stop(void);
u8 I2C_WaitAck(void);
void I2C_NAck(void);  
u8 I2C_SendByte(u8 txd);
u8 I2C_ReadByte(unsigned char ack);
/* Global functions ----------------------------------------------------------------------------------------*/
//void delayXuS(uint32_t time)
//{    
//  u16 i=0;  
//  while(time--)
//  {
//    i=1;  
//    while(i--);    
//  }
//}

/*********************************************************************************************************//**
  * @brief  I2C_SDA_SetIn.
  * @retval None
  ***********************************************************************************************************/
//void I2C_SDA_SetIn(void)
//{
//	STM_PininInit(TOUCH_I2C_SDA_IN, GPIO_PuPd_NOPULL, EXTI_Trigger_Falling, MODE_GPIO);
//}

/*********************************************************************************************************//**
  * @brief  I2C_SDA_SetOut.
  * @retval None
  ***********************************************************************************************************/
void I2C_SDA_SetOut(void)
{
//	STM_PinoutInit(TOUCH_I2C_SDA, GPIO_PuPd_NOPULL, val);
  TOUCH_I2C_SDA_HIGH();
  
    GPIO_Init(TOUCH_I2C_SDA_PROT, TOUCH_I2C_SDA_PIN, GPIO_Mode_Out_PP_Low_Fast);

  
//   GPIO_InitTypeDef  GPIO_InitStructure;
//
//  /* Enable the GPIO_LED Clock */
//  RCC_AHBPeriphClockCmd(TOUCH_I2C_SDA_GPIO_CLK, ENABLE);
//
//  /* Configure the GPIO_LED pin */
//  GPIO_InitStructure.GPIO_Pin = TOUCH_I2C_SDA_PIN;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//双向IO  //GPIO_OType_PP;  //必须
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;// GPIO_PuPd_UP; 
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;//GPIO_Speed_40MHz; //GPIO_Speed_400KHz;
//  GPIO_Init(TOUCH_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);  
}

///*********************************************************************************************************//**
//  * @brief  I2C_SCL_SetIn.
//  * @retval None
//  ***********************************************************************************************************/
//void I2C_SCL_SetIn(void)
//{
//	STM_PininInit(TOUCH_I2C_SCL_IN, GPIO_PuPd_NOPULL, EXTI_Trigger_Falling, MODE_GPIO);
//}

/*********************************************************************************************************//**
  * @brief  I2C_SCL_SetOut.
  * @retval None
  ***********************************************************************************************************/
void I2C_SCL_SetOut(void)
{
//	STM_PinoutInit(TOUCH_I2C_CLK, GPIO_PuPd_NOPULL, 1); 
    
  TOUCH_I2C_CLK_HIGH();
  
      GPIO_Init(TOUCH_I2C_CLK_PROT, TOUCH_I2C_CLK_PIN, GPIO_Mode_Out_PP_Low_Fast);

  /* Enable the GPIO_LED Clock */ 
  //GPIO_InitTypeDef  GPIO_InitStructure;

//  RCC_AHBPeriphClockCmd(TOUCH_I2C_CLK_GPIO_CLK, ENABLE);
//
//  /* Configure the GPIO_LED pin */
//  GPIO_InitStructure.GPIO_Pin = TOUCH_I2C_CLK_PIN;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;  //GPIO_OType_PP;  //必须
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;// GPIO_PuPd_UP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;  //GPIO_Speed_40MHz; //GPIO_Speed_400KHz;
//  GPIO_Init(TOUCH_I2C_CLK_GPIO_PORT, &GPIO_InitStructure);
}

/*********************************************************************************************************//**
  * @brief  TOUCH_KEY_Init.
  * @retval None
  ***********************************************************************************************************/
u8 res = 0;
u8 res1 = 0;
void TOUCH_KEY_Init(u8 initenable)  //initenable = 0x40使能key12中断，=0 为按键
{
	u8 i;
  u8 configReadBuf[MAX_INITDATE_LEN];
	u8 initData[MAX_INITDATE_LEN];
//  STM_PininInit(TOUCH_KEY_INT, GPIO_PuPd_NOPULL, EXTI_Trigger_Falling, MODE_EXTI);  //GPIO_PuPd_NOPULL
	
//  STM_PinoutInit(TOUCH_I2C_CLK, GPIO_PuPd_NOPULL, 1);
  I2C_SCL_SetOut();
  I2C_SDA_SetOut();
//  TOUCH_I2C_SDA_HIGH();
//  TOUCH_I2C_CLK_HIGH();
  
//  delayXuS(10000);
//  if(READ_SDA == 0)
//  {
//    TOUCH_I2C_SDA_LOW();
//    delayXuS(50000);
//    TOUCH_I2C_CLK_LOW();
//    delayXuS(50000);
//    TOUCH_I2C_CLK_HIGH();
//    delayXuS(50000);
//    TOUCH_I2C_SDA_HIGH();
//    delayXuS(50000);
//  }
//  I2C_Stop();
//  I2C_Stop();
//  I2C_Stop();
//  I2C_Stop();
//  I2C_Stop();
//  I2C_Stop();
//  I2C_Stop();
//  I2C_Stop();
//	delayXuS(100000);
  
	initData[0]  = 0;                         //0:终端低电平读数据有效，1：低脉冲后读数据有效
	initData[1]  = 0;                         //保留
	initData[2]  = 0x83;	                    //保留
	initData[3]  = 0xf3;	                    //保留
	initData[4]  = 0x98;	                    //bit6 LSC=0 一般省电模式，=1更省电模式，唤醒时间增至0.5-1秒 0xD8
  initData[5]  = LEVEL_TRIGGER_K1;          //K1 : key3	//bit7=0 唤醒  1不唤醒  触发门槛（8~64）
	initData[6]  = LEVEL_TRIGGER_K2;	        //K2 : key7
	initData[7]  = LEVEL_TRIGGER_K3;	        //K3 : key2
	initData[8]  = LEVEL_TRIGGER_K4;	        //K4 : key*
	initData[9]  = LEVEL_TRIGGER_K5;	        //K5 : key1
	initData[10] = LEVEL_TRIGGER_K6;	        //K6 : key8
	initData[11] = LEVEL_TRIGGER_K7;	        //K7 : key4
	initData[12] = LEVEL_TRIGGER_K8;	        //K8 : key9
	initData[13] = LEVEL_TRIGGER_K9;	        //K9 : key5
	initData[14] = LEVEL_TRIGGER_K10;	        //K10: key#
	initData[15] = LEVEL_TRIGGER_K11;         //K11: key6
  initData[16] = LEVEL_TRIGGER_K12;	        //K12: key0
  initData[17] = LEVEL_TRIGGER_K13 | 0x80;	//K13: keyFP
  initData[18] = LEVEL_TRIGGER_K14 | 0x80;	//K14: keyN
  initData[19] = LEVEL_TRIGGER_K15 | 0x80;	//K15: keyN
	initData[20] = (initenable | LEVEL_TRIGGER_K16) | 0x80;	//K16: keyIRQ
	initData[21] = 0;
	for(i=0; i<MAX_INITDATE_LEN-1; i++)
		initData[MAX_INITDATE_LEN-1] += initData[i];
    
  res = TOUCH_KEY_ReadConfig(configReadBuf);
  if(memcmp(configReadBuf, initData, MAX_INITDATE_LEN) != 0)
    res1 = I2C_BS8112aInit(initData);	
//  delayXuS(600000);
//  res = TOUCH_KEY_ReadConfig(configReadBuf);  //test:

	/*if(initenable == 0x40)
		EXTI->IMR|=1<<2;//使能key12上的中断  
	else
	    EXTI->IMR&=~(1<<2);		 //屏蔽key12中断	  */
//  EXTI_ClearITPendingBit(TOUCH_KEY_INT_EXTI_LINE);
}

/*********************************************************************************************************//**
  * @brief  I2C_BS8112aInit. 写BS8112设置寄存器
  * @retval None
  ***********************************************************************************************************/
u8 I2C_BS8112aInit(u8* p)
{
	u8 i;
  u8 iic_status = 0;
  
	iic_status = I2C_Start();
  if(iic_status == 1) {
    if(!I2C_SendByte(BS8112_ADDR << 1))
      return 0;
//    delayXuS(10); 
    if(!I2C_SendByte(REG_ADDR_WRITE_CFG))
      return 0;        
//    delayXuS(10);
    //  I2C_Stop();
    //  delayXuS(50);
    //  I2C_Start(); 
    //	I2C_SendByte(BS8112_ADDR << 1); //不能再写
    //	if(I2C_WaitAck())
    //    return 1; 
    for(i=0; i<21; i++)
    {
      if(!I2C_SendByte(*p++))
        return 0;
//      delayXuS(10);
    }
    if(!I2C_SendByte(*p))
      return 0;        
    I2C_NAck();
//    delayXuS(10);
    I2C_Stop();
    return 1;
  } 

  if(iic_status == 0) {
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
  }
  return 0;
}

/*********************************************************************************************************//**
  * @brief  I2C_Start.
  * @retval None
  ***********************************************************************************************************/
u8 I2C_ReadReg(u8 reg)
{
  u8 val;
  u8 iic_status = 0;
  
  iic_status = I2C_Start(); 
  if(iic_status == 1) {
    if(!I2C_SendByte(BS8112_ADDR << 1))
      return 0xcc;      
//    delayXuS(10);  //必须
    if(!I2C_SendByte(reg))//发送寄存器地址	
      return 0xcc;    
    I2C_Stop();   //必须
//    delayXuS(10); //必须
    
    iic_status = I2C_Start(); 
    if(iic_status == 1) { 
      if(!I2C_SendByte((BS8112_ADDR << 1) | 0x01)) //读数据
        return 0xcc;
//      delayXuS(10); //必须
      val = I2C_ReadByte(0);
//      delayXuS(10);
      I2C_Stop();
      return val;
    }
  }
  
  if(iic_status == 0) {
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
  }
  return 0xcc;  
//  delayXuS(20);  
}


//u8 TOUCH_KEY_ReadConfig(void)
//{
//	u8 i;
//  u8 val;
//	
//  for(i=0; i<22; i++) {
//    val = I2C_ReadReg(REG_ADDR_READ_CFG+i);
//    if(val != 0xcc)
//      ConfigReadBuf[i] = val;
//    else return 1;
//  }
//  return 0;
//}

/*********************************************************************************************************//**
  * @brief  TOUCH_KEY_ReadConfig.
  * @retval None
  ***********************************************************************************************************/
u8 TOUCH_KEY_ReadConfig(u8 *pBuf)
{
	u8 i;
	u8 iic_status = 0;
  
  iic_status = I2C_Start(); 
  if(iic_status == 1) {
    if(!I2C_SendByte(BS8112_ADDR << 1))
      return 0;
//    delayXuS(10); 
    if(!I2C_SendByte(REG_ADDR_READ_CFG))
      return 0;
//    delayXuS(10);	
    I2C_Stop();
    
//    delayXuS(10);
    iic_status = I2C_Start();
    if(iic_status == 1) {
      if(!I2C_SendByte((BS8112_ADDR << 1) | 0x01)) //读数据
        return 0;
//      delayXuS(10);
      
      for(i=0; i<MAX_INITDATE_LEN-1; i++) {
        pBuf[i] = I2C_ReadByte(1);	//读取数据并发送ACK
//        delayXuS(10);
      }
      
      pBuf[MAX_INITDATE_LEN-1] =  I2C_ReadByte(0);	//读取数据不发送ACK
//      delayXuS(10);
      I2C_Stop();
      return 1;
    }  
  }
  
  if(iic_status == 0) {
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
  }
  return 0;  
}

/*********************************************************************************************************//**
  * @brief  TOUCH_KEY_Get.
  * @retval None
  ***********************************************************************************************************/
u16 TOUCH_KEY_Get(void)
{
	u8 i;
	u16 temp = 0;
  u8 iic_status = 0;
  
  iic_status = I2C_Start(); 
  if(iic_status == 1) { 
    if(!I2C_SendByte(BS8112_ADDR << 1))
      return 0x00FF;
//    delayXuS(10);
    
    if(!I2C_SendByte(REG_ADDR_READ_KEY))//发送0x80寄存器地址	
      return 0x00FF;
//    delayXuS(10);
    I2C_Stop();
    
//    delayXuS(10);
    iic_status = I2C_Start(); 
    if(iic_status == 1) {
      if(!I2C_SendByte((BS8112_ADDR << 1) | 0x01)) //读数据
        return 0x00FF;
//      delayXuS(10);
      
      temp = (u16)I2C_ReadByte(1);
//      delayXuS(10);
      
      i = I2C_ReadByte(0);
//      delayXuS(10);  
      I2C_Stop();
    }
  }
  
  if(iic_status == 0) {
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
    I2C_Stop();
    return 0x00FF;
  } else if(iic_status == 0xFF) return 0x00FF;
  
  temp |= (u16)(i << 8);	
	for(i=0; i<12; i++)
	{
		if(keycode[i] == temp)
		{
			temp = i;
			return temp;
		}
	}
	return 0x00FF;
}

///*********************************************************************************************************//**
//  * @brief  TOUCH_KEY_Get.
//  * @retval None
//  ***********************************************************************************************************/
//u16 TOUCH_KEY_Get(void)
//{
//	u8 i;
//	u16 temp = 0;
//	
//	temp = (u16)I2C_ReadReg(REG_ADDR_READ_KEY);
//	i = I2C_ReadReg(REG_ADDR_READ_KEY+1);
//	
//  temp |= (u16)(i << 8);
////	I2C_Stop();
//	
//	for(i=0; i<12; i++)
//	{
//		if(keycode[i] == temp)
//		{
//			temp = i;
//			return temp;
//		}
//	}
//	return 0x00FF;
//}

/*********************************************************************************************************//**
  * @brief  I2C_Start.
  * @retval None
  ***********************************************************************************************************/
u8 I2C_Start(void)
{
  u16 timeout;

  if(READ_SCL) {
    timeout = 500;
    while(!READ_SDA && timeout>0)
    {
      timeout--;
    }
    if(READ_SDA) {
      TOUCH_I2C_SDA_HIGH();
      delayXuS(1);  
      TOUCH_I2C_CLK_HIGH();
      delayXuS(1);
      TOUCH_I2C_SDA_LOW();//START:when CLK is high,DATA change form high to low 
      delayXuS(1);
      TOUCH_I2C_CLK_LOW();//钳住I2C总线，准备发送或接收数据
      delayXuS(1);
      return 1;
    } else return 0;
  } else return 0xFF;
    
//  I2C_SCL_SetIn();
//  I2C_SDA_SetIn();
//  if(READ_SCL) {
//    timeout = 300;
//    while(!READ_SDA && timeout>0)
//    {
//      timeout--;
//    }
//    if(READ_SDA) { 
//      I2C_SDA_SetOut();
//      TOUCH_I2C_SDA_HIGH();
////      delayXuS(2);
//      I2C_SCL_SetOut();
//      TOUCH_I2C_CLK_HIGH();
//      delayXuS(5);
//      TOUCH_I2C_SDA_LOW();
//      delayXuS(5);
//      TOUCH_I2C_CLK_LOW();
//      delayXuS(5);
//      return 1;
//    } else {
//      I2C_SCL_SetOut();
//      I2C_SDA_SetOut();
//      return 0;
//    }
//  } else {
//    I2C_SCL_SetOut();
//    I2C_SDA_SetOut();
//    return 0xff;
//  }
}	

/*********************************************************************************************************//**
  * @brief  I2C_Stop.
  * @retval None
  ***********************************************************************************************************/
void I2C_Stop(void)
{
//	I2C_SDA_SetOut();	
	TOUCH_I2C_SDA_LOW();//STOP:when CLK is high DATA change form low to high
 	delayXuS(1);	 
	TOUCH_I2C_CLK_HIGH();	
	delayXuS(1);
	TOUCH_I2C_SDA_HIGH();//发送I2C总线结束信号
	delayXuS(1);
//  TOUCH_I2C_CLK_LOW();
//  delayXuS(5);
}

/*********************************************************************************************************//**
  * @brief  I2C_Ack. 产生ACK应答
  * @retval None
  ***********************************************************************************************************/
void I2C_Ack(void)
{
//  delayXuS(1);
	TOUCH_I2C_SDA_LOW();  //scl高电平期间，sda low
//  TOUCH_I2C_CLK_LOW();
  delayXuS(1);
	TOUCH_I2C_CLK_HIGH();
	delayXuS(1);
	TOUCH_I2C_CLK_LOW();
  delayXuS(1);
  TOUCH_I2C_SDA_LOW();
//  delayXuS(1);
  delayXuS(10);
//  TOUCH_I2C_SDA_HIGH();
//  delayXuS(60);
//  delayXuS(100);

//  timeout = 10000;
//  while(!READ_SCL && timeout>0)
//  {
//    timeout--;
//  }
//  if(timeout==0)
//    return 0;
//  else return 1;
}
 
/*********************************************************************************************************//**
  * @brief  I2C_NAck. 不产生ACK应答	
  * @retval None
  ***********************************************************************************************************/
void I2C_NAck(void)
{
//	TOUCH_I2C_CLK_LOW();
//  delayXuS(1);
	TOUCH_I2C_SDA_HIGH();
	delayXuS(1);
//  TOUCH_I2C_CLK_LOW();
//  delayXuS(5);
	TOUCH_I2C_CLK_HIGH();
	delayXuS(1);
	TOUCH_I2C_CLK_LOW();
  delayXuS(1);
  TOUCH_I2C_SDA_LOW();
  delayXuS(10);
//  delayXuS(60);
}
		  
/*********************************************************************************************************//**
  * @brief  I2C_WaitAck.
	* @retval 1: 接收应答失败  0: 接收应答成功
  ***********************************************************************************************************/
u8 I2C_WaitAck(void)
{
	u16 ucErrTime=0;
  	 
//	TOUCH_I2C_SDA_HIGH();
//	delayXuS(1);	   
	TOUCH_I2C_CLK_HIGH();
	delayXuS(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime > 500)
		{
      TOUCH_I2C_CLK_LOW();
      delayXuS(1);
			I2C_Stop();
      I2C_Stop();
      I2C_Stop();
      I2C_Stop();
      I2C_Stop();
      I2C_Stop();
      I2C_Stop();
      I2C_Stop();
			return 0;
		}
	}
	TOUCH_I2C_CLK_LOW();
  delayXuS(10);
//  delayXuS(60);   
	return 1;  
} 

/*********************************************************************************************************//**
  * @brief  I2C_SendByte.
  * @retval None
  ***********************************************************************************************************/
u8 I2C_SendByte(u8 data)
{                        
  u8 t;
//  u16 timeout = 0;  

//  timeout = 10000;
//  while(!READ_SCL && timeout>0)
//  {
//    timeout--;
//  }
//  if(timeout==0)
//    return;
  TOUCH_I2C_CLK_LOW();//拉低时钟开始数据传输 
//  delayXuS(1);     
	for(t=0; t<8; t++)
	{              
          if(data & 0x80) {
            
			TOUCH_I2C_SDA_HIGH();
          }else{ 
			TOUCH_I2C_SDA_LOW();
          }
    data <<= 1; 	  
		delayXuS(1);
//    TOUCH_I2C_CLK_LOW();    
		TOUCH_I2C_CLK_HIGH();
		delayXuS(2); 
		TOUCH_I2C_CLK_LOW();	
		delayXuS(1);
  }	
   
  if(!I2C_WaitAck())
    return 0;
  return 1;
} 	    

/*********************************************************************************************************//**
  * @brief  I2C_ReadByte. 读1个字节，ack=1时，发送ACK，ack=0，发送nACK
  * @retval None
  ***********************************************************************************************************/
u8 I2C_ReadByte(unsigned char ack)
{
	unsigned char i,receive=0;
//  u16 timeout = 0;

//  timeout = 10000;
//  while(!READ_SCL && timeout>0)
//  {
//    timeout--;
//  }
//  if(timeout==0)
//    return 0xCC;

//  delayXuS(10);
  TOUCH_I2C_CLK_LOW();
  TOUCH_I2C_SDA_HIGH(); //必须 
//  delayXuS(2);
  receive = 0;
  for(i=0; i<8; i++)
	{   
		TOUCH_I2C_CLK_HIGH();
		delayXuS(1);
    receive <<= 1;
		if(READ_SDA)
			receive++;    
		TOUCH_I2C_CLK_LOW();
    delayXuS(1);        
	}
	if(!ack) {    
		I2C_NAck();//发送nACK
	} else {
		I2C_Ack(); //发送ACK 
//    if(!I2C_Ack())
//      return 0x55;
  }    
	return receive;
}
