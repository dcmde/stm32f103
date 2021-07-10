#include <FreeRTOS.h>
#include <task.h>
#include "task/ctrlTask.hpp"
#include "timer.h"
#include "gpio.hpp"

void ctrl_config_timers();

void ctrl_config_pins();

[[noreturn]] void ctrlTask(void *p) {

    ctrl_config_timers();
    ctrl_config_pins();

    int8_t speed = 0;

    while (1) {

        if (++speed < 0) {
            timer_setChannelPulse(TIM3, Channel_1, 0);
            timer_setChannelPulse(TIM3, Channel_2, 128 + speed);
            timer_setChannelPulse(TIM3, Channel_3, 0);
            timer_setChannelPulse(TIM3, Channel_4, 128 + speed);
        } else {
            timer_setChannelPulse(TIM3, Channel_1, speed);
            timer_setChannelPulse(TIM3, Channel_2, 0);
            timer_setChannelPulse(TIM3, Channel_3, speed);
            timer_setChannelPulse(TIM3, Channel_4, 0);
        }
        vTaskDelay(50);
    }
}

void ctrl_config_timers() {
    timer_init(TIM3, Div_1, 360, 128, Up);
    timer_setPWM(TIM3, PWM_1, Channel_1, 0, High);
    timer_setPWM(TIM3, PWM_1, Channel_2, 0, High);
    timer_setPWM(TIM3, PWM_1, Channel_3, 0, High);
    timer_setPWM(TIM3, PWM_1, Channel_4, 0, High);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);

    timer_init(TIM1, Div_1, 0, 0xFFFF, Up);
    timer_setEncoder(TIM1, ENCODER_MODE_3, ENCODER_RISING, ENCODER_RISING);

    timer_init(TIM2, Div_1, 0, 0xFFFF, Up);
    timer_setEncoder(TIM2, ENCODER_MODE_3, ENCODER_RISING, ENCODER_RISING);
}

void ctrl_config_pins() {
    Gpio::setPin(A6, GPIO_Mode_AF_PP);
    Gpio::setPin(A7, GPIO_Mode_AF_PP);
    Gpio::setPin(B0, GPIO_Mode_AF_PP);
    Gpio::setPin(B1, GPIO_Mode_AF_PP);

    Gpio::setPin(A15, GPIO_Mode_IN_FLOATING);
    Gpio::setPin(B3, GPIO_Mode_IN_FLOATING);
    Gpio::setPin(A8, GPIO_Mode_IN_FLOATING);
    Gpio::setPin(A9, GPIO_Mode_IN_FLOATING);
}