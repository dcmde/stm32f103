#include "stm32tasks.hpp"

[[noreturn]] void my_task(void *p) {
    struct Parameters param = *((struct Parameters *) p);
    Gpio::setPin(C13, GPIO_Mode_Out_PP);
    // main loop
    while (1) {
        printf("Running... %i\n", (int) param.id);
        vTaskDelay(param.delay);
        if (Gpio::readPin(C13)) {
            Gpio::pinLow(C13);
        } else {
            Gpio::pinHigh(C13);
        }
    }
}