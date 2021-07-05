#include "task/variables.h"

QueueHandle_t refQueue = NULL;
QueueHandle_t uartQueue = NULL;
TaskHandle_t comTaskHandle = NULL;
TaskHandle_t ctrlTaskHandle = NULL;
volatile uint8_t dma_ht_flag = 0;
