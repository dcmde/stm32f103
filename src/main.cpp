#include <FreeRTOS.h>
#include <task.h>
#include <task/microSdTask.hpp>
#include <task/timerTask.hpp>

int main() {
//    xTaskCreate(microSdTask, "microSd", 128, nullptr, 1, nullptr);
    xTaskCreate(timerTask, "timer", 128, nullptr, 1, nullptr);
    vTaskStartScheduler();
    return 0;
}