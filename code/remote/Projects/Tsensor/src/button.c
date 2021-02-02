#include "button.h"
#include "iic.h"
#include "main.h"

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


void Get_Key_value(u16* key_sta)
{
  for(u8 i =0; i<16;i++){
   *key_sta =  GPIO_ReadInputDataBit(key[i].GPIOx,(GPIO_Pin_TypeDef)key[i].Pinx)  << i;
  }
}



