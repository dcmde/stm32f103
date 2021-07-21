#include <FreeRTOS.h>
#include <task.h>
#include <task/ctrlTask.hpp>
#include <task/gpsTask.hpp>
#include <task/encoderTask.hpp>
#include <task/variables.h>

#define IDLE_TASK_SIZE 50
#define STACK_SIZE      200

StaticTask_t ctrlTaskBuffer;
StackType_t ctrlTaskStack[STACK_SIZE];

StaticTask_t gpsTaskBuffer;
StackType_t gpsTaskStack[STACK_SIZE];

StaticTask_t encoderTaskBuffer;
StackType_t encoderTaskStack[STACK_SIZE];


#if configSUPPORT_STATIC_ALLOCATION
/* static memory allocation for the IDLE task */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[IDLE_TASK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize) {
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer = &xIdleStack[0];
    *pulIdleTaskStackSize = IDLE_TASK_SIZE;
}

#endif

int main() {
    gpsTaskHandle = xTaskCreateStatic(gpsTask, "com", STACK_SIZE, nullptr, 1, gpsTaskStack, &gpsTaskBuffer);
    ctrlTaskHandle = xTaskCreateStatic(ctrlTask, "ctrl", STACK_SIZE, nullptr, 1, ctrlTaskStack, &ctrlTaskBuffer);
    encoderTaskHandle = xTaskCreateStatic(encoderTask, "encoder", STACK_SIZE, nullptr, 1, encoderTaskStack,
                                          &encoderTaskBuffer);
    vTaskStartScheduler();
    return 0;
}