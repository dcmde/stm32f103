#include "task/encoderTask.hpp"
#include <gpio.hpp>
#include <stm32f10x_rcc.h>
#include <stm32f10x_tim.h>

void configureGPIO();

void configureTimer();

/**
 * @note The encoder should be powered with 5V and the input signal should have pullups.
 * This task computes the speed and the number of turns of the encoder wheel.
 * TIM1 and 2 are used with the pins A8, A9 (TIM1) and A15, B3 (TIM2).
 * @param p
 */
[[noreturn]] void encoderTask(void *p) {

    configureGPIO();
    configureTimer();

    while (1) {
        TIM1->CNT;
        TIM2->CNT;
        TIM1->CNT = 0;
        TIM2->CNT = 0;
        vTaskDelay(1000);
    }
}

void configureGPIO() {
    Gpio::setPin(A8, GPIO_Mode_IN_FLOATING);
    Gpio::setPin(A9, GPIO_Mode_IN_FLOATING);
    Gpio::setPin(A15, GPIO_Mode_IN_FLOATING);
    Gpio::setPin(B3, GPIO_Mode_IN_FLOATING);
}

void configureTimer() {
    TIM_TimeBaseInitTypeDef TIM_BaseInitStruct;

    SET_BIT(RCC->APB1ENR, RCC_APB1Periph_TIM2); // Enable peripherals clock.
    SET_BIT(RCC->APB2ENR, RCC_APB2Periph_TIM1);

    TIM_BaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_BaseInitStruct.TIM_Period = 0xFFFF;
    TIM_BaseInitStruct.TIM_Prescaler = 0x00;
    TIM_BaseInitStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_BaseInitStruct); // Configure peripherals.
    TIM_TimeBaseInit(TIM2, &TIM_BaseInitStruct);

    SET_BIT(TIM1->CR1, TIM_CR1_CEN); // Enable peripherals.
    SET_BIT(TIM2->CR1, TIM_CR1_CEN);

    TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
}