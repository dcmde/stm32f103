#ifndef VARIABLETASK_H
#define VARIABLETASK_H

#include <FreeRTOS.h>
#include <queue.h>

#ifdef __cplusplus
extern "C" {
#endif

extern QueueHandle_t refQueue;
extern QueueHandle_t uartQueue;

#ifdef __cplusplus
}
#endif

#endif //VARIABLETASK_H
