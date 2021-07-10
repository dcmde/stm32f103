#ifndef VARIABLETASK_H
#define VARIABLETASK_H

#include <FreeRTOS.h>
#include <queue.h>

#ifdef __cplusplus
extern "C" {
#endif

#define STACK_SIZE      200
#define QUEUE_LENGTH    10
#define ITEM_SIZE       sizeof(uint8_t)
#define BUFFER_LEN   74

extern QueueHandle_t refQueue;
extern QueueHandle_t uartQueue;

extern StackType_t comTaskStack[];
extern StaticTask_t comTaskBuffer;
extern TaskHandle_t comTaskHandle;
extern StaticQueue_t comStaticQueue;
extern uint8_t comQueueStorageArea[];

extern TaskHandle_t ctrlTaskHandle;
extern volatile uint8_t buffer_head, buffer_tail, idle_flag;

#ifdef __cplusplus
}
#endif

#endif //VARIABLETASK_H
