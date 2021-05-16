#include "stm32tasks.hpp"
#include "timer.hpp"
#include "gpio.hpp"

struct Parameters param2;

int main() {

    printf("Start\n");

    param2.id = 3;
    param2.delay = 1000;
    
    xTaskCreate(my_task, "task2", 128, (void *) &param2, 1, nullptr);

    vTaskStartScheduler();

    return 0;
}