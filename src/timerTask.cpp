#include <FreeRTOS.h>
#include <task.h>
#include "task/timerTask.hpp"
#include "timer.h"
#include "gpio.hpp"

[[noreturn]] void timerTask(void *p) {

    Gpio::setPin(A8, GPIO_Mode_AF_PP);
    timer_setTIM_PWM(TIM1, Div_1, 72, Channel_1, 20000, 2000, High);

    // main loop
    while (1) {
        timer_setTIMPulse(TIM1, 1000);
        vTaskDelay(1000);
        timer_setTIMPulse(TIM1, 2000);
        vTaskDelay(1000);
    }
}