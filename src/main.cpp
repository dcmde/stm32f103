#include <microSdTask.hpp>

int main() {
    xTaskCreate(microSdTask, "microSd", 128, nullptr, 1, nullptr);
    vTaskStartScheduler();
    return 0;
}