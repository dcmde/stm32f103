#include <misc.h>
#include "stm32tasks.hpp"
#include "timer.hpp"
#include "gpio.hpp"

extern "C" {
void TIM2_IRQHandler(void) {
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        if (Gpio::readPin(A6)) {
            Gpio::pinLow(A6);
        } else {
            Gpio::pinHigh(A6);
        }
    }
}
}

[[noreturn]] void my_task(void *p) {

    Gpio::setPin(A6, GPIO_Mode_Out_PP);
    Timer::set(TIM2, Div_1, 7200, 100, Up);
    Timer::setTimerInterrupt(TIM2, TIM2_IRQn, Update);

    // main loop
    while (1) {
        vTaskDelay(1000);
    }
}