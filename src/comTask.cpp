#include "task/comTask.hpp"
#include "hc12.h"
#include "usart.h"
#include "gpio.hpp"

[[noreturn]] void comTask(void *p) {
    int8_t speed = 0;
    char val;
    refQueue = xQueueCreate(1, sizeof(speed));
    uartQueue = xQueueCreate(1, sizeof(char));

    Gpio::setPin(A3, GPIO_Mode_IN_FLOATING);

    uart_configure(USART2, 9600);
    uart_configure_interrupt(USART2, USART2_IRQn);

    while (1) {
        if (uartQueue != 0) {
            if (xQueueReceive(uartQueue, &val, (TickType_t) 0)) {

            }
        }
        xQueueSend(refQueue, (void *) &speed, (TickType_t) 0);
        vTaskDelay(50);
    }
}