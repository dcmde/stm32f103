#ifndef VARIABLETASK_H
#define VARIABLETASK_H

#include <FreeRTOS.h>
#include <queue.h>

#ifdef __cplusplus
extern "C" {
#endif

#define STACK_SIZE      200
#define BUFFER_LEN   74

extern TaskHandle_t gpsTaskHandle;
extern StackType_t gpsTaskStack[];
extern StaticTask_t gpsTaskBuffer;

extern TaskHandle_t ctrlTaskHandle;
extern StackType_t ctrlTaskStack[];
extern StaticTask_t ctrlTaskBuffer;

#ifdef __cplusplus
}
#endif

#endif //VARIABLETASK_H
