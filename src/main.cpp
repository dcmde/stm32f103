#include <FreeRTOS.h>
#include <task.h>
//#include <task/ctrlTask.hpp>
#include <task/comTask.hpp>
#include <task/variables.h>

#define IDLE_TASK_SIZE 50

#if configSUPPORT_STATIC_ALLOCATION
/* static memory allocation for the IDLE task */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[IDLE_TASK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer = &xIdleStack[0];
    *pulIdleTaskStackSize = IDLE_TASK_SIZE;
}
#endif

int main() {
//    xTaskCreate(ctrlTask, "ctrl", 128, nullptr, 1, &ctrlTaskHandle);
    comTaskHandle = xTaskCreateStatic(comTask, "com", STACK_SIZE, nullptr, 1, comTaskStack, &comTaskBuffer);
    vTaskStartScheduler();
    return 0;
}