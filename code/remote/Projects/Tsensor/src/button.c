#include "button.h"
#include "iic.h"
#include "main.h"
#include "stdbool.h"

#define  KEY_1_PORT   GPIOB    
#define  KEY_1_PIN    GPIO_Pin_1

#define  KEY_2_PORT   GPIOB    
#define  KEY_2_PIN    GPIO_Pin_2

#define  KEY_3_PORT   GPIOB  
#define  KEY_3_PIN    GPIO_Pin_3

#define  KEY_4_PORT   GPIOB   
#define  KEY_4_PIN    GPIO_Pin_4

#define  KEY_5_PORT   GPIOB   
#define  KEY_5_PIN    GPIO_Pin_5

#define  KEY_6_PORT   GPIOB    
#define  KEY_6_PIN    GPIO_Pin_6

#define  KEY_7_PORT   GPIOB    
#define  KEY_7_PIN    GPIO_Pin_7

#define  KEY_8_PORT   GPIOD    
#define  KEY_8_PIN    GPIO_Pin_4

#define  KEY_9_PORT   GPIOD    
#define  KEY_9_PIN    GPIO_Pin_5
//#define  KEY_8_PORT   GPIOD    
//#define  KEY_8_PIN    GPIO_Pin_6
//
//#define  KEY_9_PORT   GPIOD    
//#define  KEY_9_PIN    GPIO_Pin_6

#define  KEY_10_PORT   GPIOD    
#define  KEY_10_PIN    GPIO_Pin_6

#define  KEY_11_PORT   GPIOD    
#define  KEY_11_PIN    GPIO_Pin_7

#define  KEY_12_PORT   GPIOC    
#define  KEY_12_PIN    GPIO_Pin_2

#define  KEY_13_PORT   GPIOC    
#define  KEY_13_PIN    GPIO_Pin_3

#define  KEY_14_PORT   GPIOC    
#define  KEY_14_PIN    GPIO_Pin_4

#define  KEY_15_PORT   GPIOC    
#define  KEY_15_PIN    GPIO_Pin_5

#define  KEY_16_PORT   GPIOC    
#define  KEY_16_PIN    GPIO_Pin_6
void button_init(void)
{
    GPIO_Init(KEY_1_PORT, KEY_1_PIN, GPIO_Mode_In_FL_No_IT);
    GPIO_Init(KEY_2_PORT, KEY_2_PIN, GPIO_Mode_In_FL_No_IT);
    GPIO_Init(KEY_3_PORT, KEY_3_PIN, GPIO_Mode_In_FL_No_IT);
    GPIO_Init(KEY_4_PORT, KEY_4_PIN, GPIO_Mode_In_FL_No_IT);
    GPIO_Init(KEY_5_PORT, KEY_5_PIN, GPIO_Mode_In_FL_No_IT);
    GPIO_Init(KEY_6_PORT, KEY_6_PIN, GPIO_Mode_In_FL_No_IT);
    GPIO_Init(KEY_7_PORT, KEY_7_PIN, GPIO_Mode_In_FL_No_IT);
    GPIO_Init(KEY_8_PORT, KEY_8_PIN, GPIO_Mode_In_FL_No_IT);
    GPIO_Init(KEY_9_PORT, KEY_9_PIN, GPIO_Mode_In_FL_No_IT);
    GPIO_Init(KEY_10_PORT, KEY_10_PIN, GPIO_Mode_In_FL_No_IT);
    GPIO_Init(KEY_11_PORT, KEY_11_PIN, GPIO_Mode_In_FL_No_IT);
    GPIO_Init(KEY_12_PORT, KEY_12_PIN, GPIO_Mode_In_FL_No_IT);
    GPIO_Init(KEY_13_PORT, KEY_13_PIN, GPIO_Mode_In_FL_No_IT);
    GPIO_Init(KEY_14_PORT, KEY_14_PIN, GPIO_Mode_In_FL_No_IT);
    GPIO_Init(KEY_15_PORT, KEY_15_PIN, GPIO_Mode_In_FL_No_IT);
    GPIO_Init(KEY_16_PORT, KEY_16_PIN, GPIO_Mode_In_FL_No_IT);
}
typedef struct{
  GPIO_TypeDef * GPIOx;
  uint8_t        Pinx;
}key_t;


key_t key[16] = {
  { KEY_1_PORT  ,KEY_1_PIN  },
  { KEY_2_PORT  ,KEY_2_PIN  },
  { KEY_3_PORT  ,KEY_3_PIN  },
  { KEY_4_PORT  ,KEY_4_PIN  },
  { KEY_5_PORT  ,KEY_5_PIN  },
  { KEY_6_PORT  ,KEY_6_PIN  },
  { KEY_7_PORT  ,KEY_7_PIN  },
  { KEY_8_PORT  ,KEY_8_PIN  },
  { KEY_9_PORT  ,KEY_9_PIN  },
  { KEY_10_PORT ,KEY_10_PIN },
  { KEY_11_PORT ,KEY_11_PIN },
  { KEY_12_PORT ,KEY_12_PIN },
  { KEY_13_PORT ,KEY_13_PIN },
  { KEY_14_PORT ,KEY_14_PIN },
  { KEY_15_PORT ,KEY_15_PIN },
  { KEY_16_PORT ,KEY_16_PIN },
};

u16 key_sta_g[16];
void Get_Key_value(u16* key_sta)
{
  u16 sta =0;
  for(u8 i =0; i<16;i++){
    key_sta_g[i] = 0;
    sta =  GPIO_ReadInputDataBit(key[i].GPIOx,(GPIO_Pin_TypeDef)key[i].Pinx) ? true :false;
    *key_sta |= sta<<i;
    key_sta_g[i] = sta;
//   break;
   
  }
//  key_sta_g =0;
//memset(key_sta_g,0x00,sizeof(u16)*16);
//  *key_sta = GPIO_ReadInputDataBit(KEY_1_PORT,KEY_1_PIN) ;key_sta_g[0] =  *key_sta;
//  *key_sta = GPIO_ReadInputDataBit(KEY_2_PORT,KEY_2_PIN) << 0;key_sta_g[1] =  *key_sta;
//  *key_sta = GPIO_ReadInputDataBit(KEY_3_PORT,KEY_3_PIN) << 2;key_sta_g[2] =  *key_sta;
//  *key_sta = GPIO_ReadInputDataBit(KEY_4_PORT,KEY_4_PIN) << 3;key_sta_g[3] =  *key_sta;
//  *key_sta = GPIO_ReadInputDataBit(KEY_5_PORT,KEY_5_PIN) << 4;key_sta_g[4] =  *key_sta;
//  *key_sta = GPIO_ReadInputDataBit(KEY_6_PORT,KEY_6_PIN) << 5;key_sta_g[5] =  *key_sta;
//  *key_sta = GPIO_ReadInputDataBit(KEY_7_PORT,KEY_7_PIN) << 6;key_sta_g[6] =  *key_sta;
//  *key_sta = GPIO_ReadInputDataBit(KEY_8_PORT,KEY_8_PIN) << 7;key_sta_g[7] =  *key_sta;
//  *key_sta = GPIO_ReadInputDataBit(KEY_9_PORT,KEY_9_PIN) << 8;key_sta_g[8] =  *key_sta;
//  *key_sta = GPIO_ReadInputDataBit(KEY_10_PORT,KEY_10_PIN) << 9;key_sta_g[9] =  *key_sta;
//  *key_sta = GPIO_ReadInputDataBit(KEY_11_PORT,KEY_12_PIN) << 10;key_sta_g[10] =  *key_sta;
//  *key_sta = GPIO_ReadInputDataBit(KEY_12_PORT,KEY_12_PIN) << 11;key_sta_g[11] =  *key_sta;
//  *key_sta = GPIO_ReadInputDataBit(KEY_13_PORT,KEY_13_PIN) << 12;key_sta_g[12] =  *key_sta;
//  *key_sta = GPIO_ReadInputDataBit(KEY_14_PORT,KEY_14_PIN) << 13;key_sta_g[13] =  *key_sta;
//  *key_sta = GPIO_ReadInputDataBit(KEY_15_PORT,KEY_15_PIN) << 14;key_sta_g[14] =  *key_sta;
//  *key_sta = GPIO_ReadInputDataBit(KEY_16_PORT,KEY_16_PIN) << 15;key_sta_g[15] =  *key_sta;
//  key_sta_g =  *key_sta;
}



