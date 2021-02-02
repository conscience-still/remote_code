#include "button.h"
#include "iic.h"
#include "main.h"
#include "stdio.h"

u8 CheckSum(u8* data, u8 len)// V
{
    u8 i;
    u8 sum;
    
    sum = 0;
    for(i = 0; i < len; i++)
    {
        sum += data[i];
    }
    return sum;
}

void button_init(void)
{
  IIC_Init(0);
}
void test_init(void)
{
    u8 data[22] = {0,0,0x83,0xf3};
    
    data[0] = 0x00;
//    I2C_BufferWrite(ADDRESS_Write, IRQ_OMS,1, &data[0]);
    
    data[4]  = 0x40;
//    I2C_BufferWrite(ADDRESS_Write, LSC,1, &data[4]);
   
    /*д╛хо╩╫пя*/
    data[21]  = CheckSum(data,21);
    I2C_BufferWrite(ADDRESS_Write, LSC,22, data);
}

void test_read(void)
{
  u8 temp = 0;
  I2C_BufferRead(ADDRESS_Write, KeyStatus0,1, &temp);
  printf("read key status:%d\r\n",temp);
  I2C_BufferRead(ADDRESS_Write, KeyStatus1,1, &temp);
  printf("read key status:%d\r\n",temp);
}

