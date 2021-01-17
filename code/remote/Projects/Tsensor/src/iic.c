#include "iic.h"
#include "main.h"


void IIC_Init(unsigned char Addr)
{
 GPIO_Init(GPIOC, GPIO_Pin_0, GPIO_Mode_Out_OD_HiZ_Slow);
 GPIO_Init(GPIOC, GPIO_Pin_1, GPIO_Mode_Out_OD_HiZ_Slow);
                CLK_PeripheralClockConfig(CLK_Peripheral_I2C1, ENABLE);
  /* I2C  clock Enable*/
  CLK_PeripheralClockConfig(CLK_Peripheral_I2C1, ENABLE);  
  
  /* Initialize I2C peripheral */
  I2C_Init(I2C1,40000, Addr, //I2C_MAX_FAST_FREQ
           I2C_Mode_I2C, I2C_DutyCycle_2,
           I2C_Ack_Enable, I2C_AcknowledgedAddress_7bit);
}
void I2C_BufferWrite(u8 SLAVE_ADDRESS,u16 WriteAddr,u8 NumByte,u8* pBuffer)//I2CD¡äo¡¥¨ºy
{
    while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));//??¨¨????¡§¦Ì?¡À¨º??¡Á¡ä¨¬?¡ê¡§?D??¡Á¨¹??¡¤¡À?|¡Á¡ä¨¬?¡ê?
    
    I2C_GenerateSTART(I2C1, ENABLE);
     while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));//?¨¬2a???¡§D?o?¡Á¡ä¨¬?¡ê¡§EV5¨º??t¡ê?¨¨?1???¨®D¡¤¡é?¨ª¨ª¨º3¨¦?¨²?a¨¤?¦Ì¨¨¡äy¡ê?¡Á¡é¨°a¡ê?o?¦Ì?¨®|¨®?

     I2C_Send7bitAddress(I2C1,SLAVE_ADDRESS+((WriteAddr/256)<<1),I2C_Direction_Transmitter);//2?¡ä¨®¨®¨²24C16¦Ì??¡Â?t¦Ì??¡¤
     while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    
    I2C_SendData(I2C1,(u8)(WriteAddr));//¦Ì¨ª8??¡Á??¨²¦Ì??¡¤
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTING));//¡ê¡§EV8¨º??t¡ê?
    
    while(NumByte--)
    {
        I2C_SendData(I2C1,*pBuffer);
        pBuffer++;
        
        if(NumByte==0)
        {
            while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
        }
        else
        {
            while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTING));
        }        
    }
    I2C_GenerateSTOP(I2C1,ENABLE);  //¨ª¡ê?1D?o?   
}

void I2C_BufferRead(u8 SLAVE_ADDRESS,u16 ReadAddr,u8 NumByte,u8* pBuffer)
{
    while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
    I2C_GenerateSTART(I2C1,ENABLE);    
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
    
//    if(EE_TYPE>AT24C16)
//    {
//        I2C_Send7bitAddress(I2C1,SLAVE_ADDRESS,I2C_Direction_Transmitter);
//        while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
//        
//        I2C_SendData(I2C1,(u8)(ReadAddr>>8));
//        while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTING));
//    }
//    else
    {   //1010 000 0
        I2C_Send7bitAddress(I2C1,SLAVE_ADDRESS+((ReadAddr/256)<<1),I2C_Direction_Transmitter);
        while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    }
    
    I2C_SendData(I2C1,(u8)(ReadAddr));
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTING));
    
    I2C_GenerateSTART(I2C1,ENABLE);    
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
    
    I2C_Send7bitAddress(I2C1,SLAVE_ADDRESS,I2C_Direction_Receiver);
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    
    while(NumByte)
    {
        if(NumByte==1)
        {
            I2C_AcknowledgeConfig(I2C1,DISABLE);
            I2C_GenerateSTOP(I2C1,ENABLE); 
        }
        
        if(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED))
        {
            *pBuffer=I2C_ReceiveData(I2C1);
            pBuffer++;
            NumByte--;
        }
    }
    
    I2C_AcknowledgeConfig(I2C1,ENABLE);
}
 void i2c_ByteWrite(u8 I2C_Slave_Adress,u8 iData, u16 WriteAddr)
 {  
      I2C_GenerateSTART(I2C1,ENABLE);
      //I2C_Event_TypeDef teste = I2C_GetLastEvent(I2C1);
      
      while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
 
      I2C_Send7bitAddress(I2C1,(uint8_t)I2C_Slave_Adress<<1,I2C_Direction_Receiver);
      
      while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));//This while never stops
      
       /* Send Address (on 2 bytes) of first byte to be written & wait event detection */
      I2C_SendData(I2C1,(u8)(WriteAddr >> 8)); /* MSB */
      /* Test on EV8 and clear it */
      while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
      I2C_SendData(I2C1,(u8)(WriteAddr & 0xFF)); /* LSB */
      /* Test on EV8 and clear it */
     while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
      
      /* Send the byte to be written */
      I2C_SendData(I2C1,iData); 
        
      /* Test on EV8 and clear it */
      while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
      
      /* Send STOP condition */
      I2C_SendData(I2C1,iData);
     I2C_GenerateSTOP(I2C1,ENABLE);
     
     
     while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
     
     I2C_GenerateSTOP(I2C1,ENABLE);
    //}
 }  
