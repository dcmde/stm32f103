#ifndef VARIABLETASK_H
#define VARIABLETASK_H

#include <FreeRTOS.h>
#include <queue.h>

#ifdef __cplusplus
extern "C" {
#endif

extern TaskHandle_t gpsTaskHandle;
extern TaskHandle_t ctrlTaskHandle;
extern TaskHandle_t encoderTaskHandle;
extern TaskHandle_t comTaskHandle;

#ifdef __cplusplus
}
#endif

#endif //VARIABLETASK_H
