#include <stm32f10x_dma.h>
#include <nmea.h>
#include "task/gpsTask.hpp"
#include "usart.h"
#include "gpio.hpp"

void configure_DMA();

const uint8_t gps_buffer_len = 74;
char nmeaBuffer[gps_buffer_len], tempBuffer[gps_buffer_len];

[[noreturn]] void gpsTask(void *p) {
    uint8_t gps_buffer_head = (gps_buffer_len - 1), gps_buffer_tail;
    gpggl_t gpggl;

    Gpio::setPin(A3, GPIO_Mode_IN_FLOATING);

    uart_configure(USART2, 9600);
    uart_configure_interrupt(USART2, USART2_IRQn, USART_IT_IDLE);
    configure_DMA();

    while (1) {
        if (xTaskNotifyWait(0, 0, NULL, portMAX_DELAY) == pdTRUE) {
            gps_buffer_tail = (gps_buffer_head + 1) % gps_buffer_len;
            gps_buffer_head = gps_buffer_len - DMA1_Channel6->CNDTR - 1;
            if (nmeaBuffer[gps_buffer_head] == '\n' && nmeaBuffer[gps_buffer_tail] == '$') {
                uint8_t j = 0;
                if (nmeaBuffer[(gps_buffer_tail + 4) % gps_buffer_len] == 'L') {
                    for (uint8_t i = gps_buffer_tail; i != gps_buffer_head; i = (i + 1) % gps_buffer_len) {
                        tempBuffer[j++] = nmeaBuffer[i];
                    }
                    nmea_decode_gpggl(&gpggl, tempBuffer, j);
                }
            }
        }
    }
}

void configure_DMA() {
    DMA_InitTypeDef DMA_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(DMA1_Channel6);
    DMA_InitStructure.DMA_BufferSize = gps_buffer_len;
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

    DMA_Cmd(DMA1_Channel6, ENABLE);
    USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);
}