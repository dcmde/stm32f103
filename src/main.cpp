#include <FreeRTOS.h>
#include <task.h>
#include <task/ctrlTask.hpp>
#include <task/comTask.hpp>
#include <task/variables.h>

int main() {
    xTaskCreate(ctrlTask, "ctrl", 128, nullptr, 1, &ctrlTaskHandle);
    xTaskCreate(comTask, "com", 128, nullptr, 1, &comTaskHandle);
    vTaskStartScheduler();
    return 0;
}