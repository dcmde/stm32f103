#include <stm32f10x.h>
#include <cstdio>

#include "FreeRTOS.h"
#include "task.h"
#include "gpio.hpp"

struct Parameters {
    uint32_t id;
    TickType_t delay;
};

[[noreturn]] void my_task(void *p) {

    struct Parameters param = *((struct Parameters *) p);
    Gpio::setPin(PIN_13, GPIOC, GPIO_Mode_Out_PP);

    // main loop
    while (1) {
        printf("Running... %i\n", (int) param.id);
        vTaskDelay(param.delay);
        if (Gpio::readPin(PIN_13, GPIOC)) {
            Gpio::pinLow(PIN_13, GPIOC);
        } else {
            Gpio::pinHigh(PIN_13, GPIOC);
        }
    }
}

struct Parameters param1;
struct Parameters param2;

int main() {

    printf("Start\n");

    param1.id = 1;
    param1.delay = 600;

    param2.id = 3;
    param2.delay = 1000;

    xTaskCreate(my_task, "task1", 128, (void *) &param1, 1, nullptr);
    xTaskCreate( my_task, "task2", 128, (void*)&param2, 1, nullptr );

    vTaskStartScheduler();

    return 0;
}