#include <FreeRTOS.h>
#include <task.h>
#include <task/microSdTask.hpp>
#include <task/CtrlTask.hpp>

int main() {
//    xTaskCreate(microSdTask, "microSd", 128, nullptr, 1, nullptr);
    xTaskCreate(ctrlTask, "ctrl", 128, nullptr, 1, nullptr);
    vTaskStartScheduler();
    return 0;
}