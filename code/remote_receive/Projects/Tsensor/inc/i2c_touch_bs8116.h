/*********************************************************************************************************//**
 * @file    i2c_touch_bs8116.h
 * @version V1.00
 * @date    06/24/2016
 * @brief   The header file of i2c_touch_bs8116.c
 ************************************************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __I2C_TOUCH_BS8116_H
#define __I2C_TOUCH_BS8116_H

#ifdef __cplusplus
 extern "C" {
#endif
	 
/* Includes ------------------------------------------------------------------------------------------------*/ 
//#include "stm32l1xx.h"
#include "main.h"
/* Settings ------------------------------------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------------------------------------*/
//typedef struct
//{
//  uint8_t KeyInt;
//  uint8_t KeyBuf;
//  uint16_t KeyCode;
//} TOUCH_Typedef;
   
/* Exported constants --------------------------------------------------------------------------------------*/
 #define TOUCH_I2C_CLK_PROT  GPIOC
#define TOUCH_I2C_CLK_PIN   GPIO_Pin_1


#define TOUCH_I2C_SDA_PROT  GPIOC
#define TOUCH_I2C_SDA_PIN   GPIO_Pin_0
/* Exported macro ------------------------------------------------------------------------------------------*/
#define BS8112_ADDR           				0x50
#define REG_ADDR_WRITE_CFG    				0xB0
#define REG_ADDR_READ_CFG     				0xB0
#define REG_ADDR_READ_KEY     				0x08
#define KEY12_INT_ENABLE      				0x40
#define KEY12_INT_DISABLE     				0x00

#define MAX_INITDATE_LEN              22

#define LEVEL_TRIGGER               	18
#define LEVEL_TRIGGER_K1             	LEVEL_TRIGGER //key3
#define LEVEL_TRIGGER_K2             	LEVEL_TRIGGER //key7
#define LEVEL_TRIGGER_K3             	LEVEL_TRIGGER //key2
#define LEVEL_TRIGGER_K4             	LEVEL_TRIGGER //key*
#define LEVEL_TRIGGER_K5             	LEVEL_TRIGGER //key1
#define LEVEL_TRIGGER_K6             	LEVEL_TRIGGER //key8
#define LEVEL_TRIGGER_K7             	LEVEL_TRIGGER //key4
#define LEVEL_TRIGGER_K8             	LEVEL_TRIGGER;//8             //key9
#define LEVEL_TRIGGER_K9             	LEVEL_TRIGGER //key5
#define LEVEL_TRIGGER_K10            	LEVEL_TRIGGER;//8             //key#
#define LEVEL_TRIGGER_K11            	LEVEL_TRIGGER;             //key6
#define LEVEL_TRIGGER_K12            	LEVEL_TRIGGER //key0
#define LEVEL_TRIGGER_K13            	LEVEL_TRIGGER //keyN
#define LEVEL_TRIGGER_K14            	LEVEL_TRIGGER //keyN
#define LEVEL_TRIGGER_K15            	LEVEL_TRIGGER //keyN
#define LEVEL_TRIGGER_K16            	LEVEL_TRIGGER //keyIRQ

/* Exported functions --------------------------------------------------------------------------------------*/
//extern TOUCH_Typedef gTouch;
void TOUCH_KEY_Init(u8 IntEnable);
u16 TOUCH_KEY_Get(void);
u8 TOUCH_KEY_ReadConfig(u8 *pBuf);

#ifdef __cplusplus
}
#endif

#endif /* __I2C_TOUCH_BS8116_H -----------------------------------------------------------------------------*/
