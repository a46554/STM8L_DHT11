#include "stm8l15x.h"
#include "DHT11_LIB.h"
#include "Timer.h"

void TIM2_Init()
{
    CLK_PeripheralClockConfig(CLK_Peripheral_TIM2 , ENABLE);  //enable timer 2 clk
    TIM2_TimeBaseInit(TIM2_Prescaler_1 , TIM2_CounterMode_Up , 16000); //wait for 1m sec
}

void Delayms(unsigned int us)
{

    TIM2_ARRPreloadConfig(ENABLE);  //enable timer2 auto load
    TIM2_Cmd(ENABLE);               //enable timer2 conut
    while(us--) {
        while( TIM2_GetFlagStatus(TIM2_FLAG_Update) == RESET); //wait for 1u sec
        TIM2_ClearFlag(TIM2_FLAG_Update);  //clear flag
    }
    TIM2_Cmd(DISABLE);                   //disable timer2
}

void TIM3_Init()
{
    CLK_PeripheralClockConfig(CLK_Peripheral_TIM3 , ENABLE);  //enable timer 2 clk
    TIM3_TimeBaseInit(TIM3_Prescaler_1 , TIM3_CounterMode_Up , 160); // 1u sec
}

void Delay10Us(unsigned int us)
{

    TIM3_ARRPreloadConfig(ENABLE);  //enable timer2 auto load
    TIM3_Cmd(ENABLE);               //enable timer2 conut
    while(us--) {
        while( TIM3_GetFlagStatus(TIM3_FLAG_Update) == RESET); //wait for 1u sec
        TIM3_ClearFlag(TIM3_FLAG_Update);  //clear flag
    }
    TIM3_Cmd(DISABLE);                   //disable timer2
}


void main()
{
    disableInterrupts();

    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);

    TIM3_Init();
    TIM2_Init();

    enableInterrupts();

    unsigned char tmp[4];
    
    while(1) {

        GetDHT11_Data(tmp);
        Delayms(2000);

    }
}

