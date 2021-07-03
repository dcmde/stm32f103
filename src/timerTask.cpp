#include <FreeRTOS.h>
#include <task.h>
#include "task/timerTask.hpp"
#include "timer.h"
#include "gpio.hpp"
#include <stdio.h>

[[noreturn]] void timerTask(void *p) {

    Gpio::setPin(A0, GPIO_Mode_AF_PP);
    Gpio::setPin(A1, GPIO_Mode_AF_PP);
    Gpio::setPin(A8, GPIO_Mode_IN_FLOATING);
    Gpio::setPin(A9, GPIO_Mode_IN_FLOATING);
    timer_init(TIM2, Div_1, 360, 128, Up);
    timer_setPWM(TIM2, PWM_1, Channel_1, 0, High);
    timer_setPWM(TIM2, PWM_1, Channel_2, 0, High);

    timer_init(TIM1, Div_1, 0, 0xFFFF, Up);
    timer_setEncoder(TIM1, ENCODER_MODE_3, ENCODER_RISING, ENCODER_RISING);

    int8_t speed = 0;

    // main loop
    while (1) {
        if (speed < 0) {
            timer_setChannelPulse(TIM2, Channel_1, 0);
            timer_setChannelPulse(TIM2, Channel_2, ~speed);
        } else {
            timer_setChannelPulse(TIM2, Channel_1, speed);
            timer_setChannelPulse(TIM2, Channel_2, 0);
        }
        vTaskDelay(500);
        printf("Encoder %i\n", timer_getEncoderCount(TIM1));
        ++speed;
    }
}