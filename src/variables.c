#include "task/variables.h"

TaskHandle_t gpsTaskHandle;
StaticTask_t gpsTaskBuffer;
StackType_t gpsTaskStack[STACK_SIZE];

TaskHandle_t ctrlTaskHandle = NULL;
