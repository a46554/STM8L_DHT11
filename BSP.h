#include "stm8l15x.h"


#define     DHT11_Low()                GPIO_WriteBit(GPIOD , GPIO_Pin_4 ,RESET)
#define     DHT11_High()               GPIO_WriteBit(GPIOD , GPIO_Pin_4 ,SET)
#define     DHT11_Read()               GPIO_ReadInputDataBit(GPIOD , GPIO_Pin_4)
#define     DHT11_OUT()                GPIO_Init(GPIOD , GPIO_Pin_4 , GPIO_Mode_Out_OD_Low_Fast); //set DHT11 output
#define     DHT11_IN()                 GPIO_Init(GPIOD , GPIO_Pin_4 , GPIO_Mode_In_PU_No_IT);  //set DHT11 input
