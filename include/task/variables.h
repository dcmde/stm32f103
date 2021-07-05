#ifndef VARIABLETASK_H
#define VARIABLETASK_H

#include <FreeRTOS.h>
#include <queue.h>

#ifdef __cplusplus
extern "C" {
#endif

extern QueueHandle_t refQueue;
extern QueueHandle_t uartQueue;
extern TaskHandle_t comTaskHandle;
extern TaskHandle_t ctrlTaskHandle;
extern volatile uint8_t dma_ht_flag;

#ifdef __cplusplus
}
#endif

#endif //VARIABLETASK_H
