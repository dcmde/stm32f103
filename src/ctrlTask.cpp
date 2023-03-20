#include <FreeRTOS.h>
#include <task.h>
#include <stm32f10x_usart.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_dma.h>
#include <misc.h>
#include "task/ctrlTask.hpp"
#include "timer.h"
#include "gpio.hpp"

int8_t joyStickInput[3];

void ctrl_config_timers();

void ctrl_config_pins();

void configureUART();

[[noreturn]] void ctrlTask(void *p) {

    int8_t rightSpeed, leftSpeed;

    ctrl_config_timers();
    ctrl_config_pins();
    configureUART();

    while (1) {
        if (xTaskNotifyWait(0, 0, NULL, portMAX_DELAY) == pdTRUE) {
            rightSpeed = joyStickInput[1];
            leftSpeed = joyStickInput[1];

            if (joyStickInput[2] < 0) {
                leftSpeed -= joyStickInput[2];
            } else {
                rightSpeed += joyStickInput[2];
            }

            if (rightSpeed > 0) {
                timer_setChannelPulse(TIM3, Channel_1, 0);
                timer_setChannelPulse(TIM3, Channel_2, rightSpeed);
            } else {
                timer_setChannelPulse(TIM3, Channel_1, -rightSpeed);
                timer_setChannelPulse(TIM3, Channel_2, 0);
            }
            if (leftSpeed > 0) {
                timer_setChannelPulse(TIM3, Channel_3, 0);
                timer_setChannelPulse(TIM3, Channel_4, leftSpeed);
            } else {
                timer_setChannelPulse(TIM3, Channel_3, -leftSpeed);
                timer_setChannelPulse(TIM3, Channel_4, 0);
            }
        }
    }
}

void ctrl_config_timers() {
    timer_init(TIM3, Div_1, 3600, 128, Up);
    timer_setPWM(TIM3, PWM_1, Channel_1, 0, High);
    timer_setPWM(TIM3, PWM_1, Channel_2, 0, High);
    timer_setPWM(TIM3, PWM_1, Channel_3, 0, High);
    timer_setPWM(TIM3, PWM_1, Channel_4, 0, High);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);

    timer_init(TIM1, Div_1, 0, 0xFFFF, Up);
    timer_setEncoder(TIM1, ENCODER_MODE_3, ENCODER_RISING, ENCODER_RISING);

    timer_init(TIM2, Div_1, 0, 0xFFFF, Up);
    timer_setEncoder(TIM2, ENCODER_MODE_3, ENCODER_RISING, ENCODER_RISING);
}

void ctrl_config_pins() {
    Gpio::setPin(A6, GPIO_Mode_AF_PP);
    Gpio::setPin(A7, GPIO_Mode_AF_PP);
    Gpio::setPin(B0, GPIO_Mode_AF_PP);
    Gpio::setPin(B1, GPIO_Mode_AF_PP);

    Gpio::setPin(A15, GPIO_Mode_IN_FLOATING);
    Gpio::setPin(B3, GPIO_Mode_IN_FLOATING);
    Gpio::setPin(A8, GPIO_Mode_IN_FLOATING);
    Gpio::setPin(A9, GPIO_Mode_IN_FLOATING);
}

void configureUART() {
    USART_InitTypeDef USART_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    DMA_InitTypeDef DMA_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    SET_BIT(RCC->APB2ENR, RCC_APB2Periph_AFIO);   // Eanble AFIO peripheral clock.
    SET_BIT(RCC->APB2ENR, RCC_APB2Periph_USART1); // Enable UART peripheral clock.

    Gpio::setPin(B7, GPIO_Mode_IN_FLOATING);

    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStruct);

    USART_InitStruct.USART_BaudRate = 9600;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStruct);

    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);

    SET_BIT(USART1->CR1, 0x2000);   // Enable peripheral.

    DMA_DeInit(DMA1_Channel5);
    DMA_InitStructure.DMA_BufferSize = 3;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) joyStickInput;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) (&(USART1->DR));
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_Init(DMA1_Channel5, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel5, ENABLE);
    USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
}