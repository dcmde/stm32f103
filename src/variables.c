#include "task/variables.h"

QueueHandle_t refQueue = NULL;

QueueHandle_t uartQueue = NULL;
StaticTask_t comTaskBuffer;
StackType_t comTaskStack[STACK_SIZE];
TaskHandle_t comTaskHandle;
StaticQueue_t comStaticQueue;

uint8_t comQueueStorageArea[ITEM_SIZE * QUEUE_LENGTH];

TaskHandle_t ctrlTaskHandle = NULL;
volatile uint8_t buffer_head = (BUFFER_LEN - 1), buffer_tail, idle_flag = 0;
