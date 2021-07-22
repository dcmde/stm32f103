#include "task/comTask.hpp"
#include <stm32f10x_usart.h>
#include <stm32f10x_rcc.h>
#include <misc.h>
#include <gpio.hpp>

void configureUART();

[[noreturn]] void comTask(void *p) {

    configureUART();

    while (1) {
        if (xTaskNotifyWait(0, 0, NULL, portMAX_DELAY) == pdTRUE) {
            USART1->DR;
        }
    }
}

void configureUART() {
    USART_InitTypeDef USART_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    Gpio::setPin(B7, GPIO_Mode_IN_FLOATING);


    SET_BIT(RCC->APB2ENR, RCC_APB2Periph_AFIO);   // Eanble AFIO peripheral clock.
    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStruct);

    SET_BIT(RCC->APB2ENR, RCC_APB2Periph_USART1); // Enable UART peripheral clock.

    USART_InitStruct.USART_BaudRate = 9600;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStruct);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    SET_BIT(USART1->CR1, 0x2000);   // Enable peripheral.
}