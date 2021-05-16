#include "stm32tasks.hpp"
#include "timer.hpp"
#include "gpio.hpp"

[[noreturn]] void my_task(void *p) {

    Gpio::setPin(C13, GPIO_Mode_Out_PP);

    Gpio::setPin(A8, GPIO_Mode_AF_PP);

    Timer::setTIM_PWM(TIM1, Div_1, 72, Channel_1, 20000, 2000);

    // main loop
    while (1) {
        Timer::setTIMPulse(TIM1, 1000);
        vTaskDelay(1000);
        Timer::setTIMPulse(TIM1, 2000);
        vTaskDelay(1000);
    }
}