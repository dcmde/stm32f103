#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"

int main() {

    SysTick_Config(72);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    GPIO_InitTypeDef gpioInitTypeDef;
    gpioInitTypeDef.GPIO_Speed = GPIO_Speed_2MHz;
    gpioInitTypeDef.GPIO_Pin = GPIO_Pin_5;
    gpioInitTypeDef.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA,&gpioInitTypeDef);

    gpioInitTypeDef.GPIO_Speed = GPIO_Speed_2MHz;
    gpioInitTypeDef.GPIO_Pin = GPIO_Pin_6;
    gpioInitTypeDef.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA,&gpioInitTypeDef);


    TIM_TimeBaseInitTypeDef timeBaseInitTypeDef;
    timeBaseInitTypeDef.TIM_ClockDivision = TIM_CKD_DIV1;
    timeBaseInitTypeDef.TIM_CounterMode = TIM_CounterMode_Up;
    timeBaseInitTypeDef.TIM_Prescaler = 0;
    timeBaseInitTypeDef.TIM_Period = 140;

    TIM_OCInitTypeDef timOcInitTypeDef;

    timOcInitTypeDef.TIM_Pulse = 70;
    timOcInitTypeDef.TIM_OCMode = TIM_OCMode_Timing;
    TIM_OC1Init(TIM2,&timOcInitTypeDef);

    TIM_ITConfig(TIM2,TIM2_IRQn,ENABLE);

    NVIC_EnableIRQ(TIM2_IRQn);

    TIM_Cmd(TIM2,ENABLE);

    uint32_t i = 0;
    while(1){
        i++;
    }


    return 0;
}

void TIM2_IRQHandler(void){

}