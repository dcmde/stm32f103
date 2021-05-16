#include <stm32tasks.hpp>

int main() {
    xTaskCreate(my_task, "task", 128, nullptr, 1, nullptr);
    vTaskStartScheduler();
    return 0;
}