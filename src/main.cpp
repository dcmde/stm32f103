#include <FreeRTOS.h>
#include <task.h>
#include <task/ctrlTask.hpp>
#include <task/comTask.hpp>

int main() {
    xTaskCreate(ctrlTask, "ctrl", 128, nullptr, 1, nullptr);
    xTaskCreate(comTask, "com", 128, nullptr, 1, nullptr);
    vTaskStartScheduler();
    return 0;
}