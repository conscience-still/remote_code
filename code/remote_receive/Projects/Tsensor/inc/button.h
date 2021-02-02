#ifndef __BUTTON_H
#define __BUTTON_H

#include "main.h"

u8 CheckSum(u8* data, u8 len);// V


#define	ADDRESS_Write   SlaveAddress | 0x00                //
#define	ADDRESS_Read    SlaveAddress | 0x01	                //

#define	IRQ_OMS		0xB0	//电0: Level hold ( 低有效 )1: One-shot ( 低有效 )
#define	LSC		0xB4	//0: 一般省电模式1: 更省电模式 ( 唤醒时间增加至 0.5 ~1 秒 )
#define	KnWU		0xB5	// Key n 触发门坎值 0: 开启按键唤醒功能 1: 关闭按键唤醒功能  0B5H~0C4H

#define	KeyStatus0	0x08	//触摸按键的输出寄存器 0= 松键， 1= 按键
#define	KeyStatus1	0x09	// 

#define ADDRESS     0x50 // address pin low (GND), default for InvenSense evaluation board
#define SlaveAddress     (ADDRESS<<1)//IIC写入时的地址字节数据，+1为读取


void button_init(void);
void test_init(void);

#endif /* __DELAY_H*/


