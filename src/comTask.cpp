#include <stm32f10x_dma.h>
#include <misc.h>
#include <cstdio>
#include "task/comTask.hpp"
#include "hc12.h"
#include "usart.h"
#include "gpio.hpp"

void configure_DMA();

uint32_t bufferSize = 6;
char nmeaBuffer[6];

[[noreturn]] void comTask(void *p) {
    int8_t speed = 0;
    char val;

    refQueue = xQueueCreate(1, sizeof(speed));
    uartQueue = xQueueCreate(1, sizeof(char));

    Gpio::setPin(A3, GPIO_Mode_IN_FLOATING);

    uart_configure(USART2, 9600);
    uart_configure_interrupt(USART2, USART2_IRQn, USART_IT_IDLE);
    configure_DMA();

    while (1) {
//        if (uartQueue != 0) {
//            if (xQueueReceive(uartQueue, &val, (TickType_t) 0)) {
//
//            }
//        }
        vTaskDelay(500);
    }
}

void configure_DMA() {
    DMA_InitTypeDef DMA_InitStructure;
    NVIC_InitTypeDef nvicInitStruct;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    nvicInitStruct.NVIC_IRQChannelSubPriority = 0;
    nvicInitStruct.NVIC_IRQChannel = DMA1_Channel6_IRQn;
    nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 4;
    nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvicInitStruct);
    NVIC_EnableIRQ(DMA1_Channel6_IRQn);

    DMA_DeInit(DMA1_Channel6);
    DMA_InitStructure.DMA_BufferSize = bufferSize;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) nmeaBuffer;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) (USART2_BASE + 0x04);
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_Init(DMA1_Channel6, &DMA_InitStructure);
    DMA1_Channel6->CCR |= (DMA_CCR6_TCIE | DMA_CCR6_HTIE);
    DMA_Cmd(DMA1_Channel6, ENABLE);
    USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);

}