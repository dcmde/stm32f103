#include "stm32tasks.hpp"

struct Parameters param;

int main() {

    xTaskCreate(my_task, "task", 128, (void *) &param, 1, nullptr);

    vTaskStartScheduler();

    return 0;
}