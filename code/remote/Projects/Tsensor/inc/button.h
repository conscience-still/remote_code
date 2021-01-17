#ifndef __BUTTON_H
#define __BUTTON_H

#include "main.h"

u8 CheckSum(u8* data, u8 len);// V


#define	ADDRESS_Write   SlaveAddress | 0x00                //
#define	ADDRESS_Read    SlaveAddress | 0x01	                //

#define	IRQ_OMS		0xB0	//��0: Level hold ( ����Ч )1: One-shot ( ����Ч )
#define	LSC		0xB4	//0: һ��ʡ��ģʽ1: ��ʡ��ģʽ ( ����ʱ�������� 0.5 ~1 �� )
#define	KnWU		0xB5	// Key n �����ſ�ֵ 0: �����������ѹ��� 1: �رհ������ѹ���  0B5H~0C4H

#define	KeyStatus0	0x08	//��������������Ĵ��� 0= �ɼ��� 1= ����
#define	KeyStatus1	0x09	// 

#define ADDRESS     0x50 // address pin low (GND), default for InvenSense evaluation board
#define SlaveAddress     (ADDRESS<<1)//IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ


void button_init(void);
void test_init(void);

#endif /* __DELAY_H*/


