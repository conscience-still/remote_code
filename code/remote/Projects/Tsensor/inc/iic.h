#ifndef __IIC_H
#define __IIC_H

#include "main.h"

void IIC_Init(unsigned char Addr);
void I2C_BufferWrite(u8 SLAVE_ADDRESS,u16 WriteAddr,u8 NumByte,u8* pBuffer);
void I2C_BufferRead(u8 SLAVE_ADDRESS,u16 ReadAddr,u8 NumByte,u8* pBuffer);
#endif /* __DELAY_H*/

