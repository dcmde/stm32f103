#include "stm32tasks.hpp"

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