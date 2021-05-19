#include <cstdio>
#include <diskio.h>
#include <FreeRTOS.h>
#include <ff.h>
#include <gpio.hpp>
#include <misc.h>
#include <spi.h>
#include <task.h>
#include <task/microSdTask.hpp>
#include <timer.hpp>

FATFS FatFs;
FIL fil;

[[noreturn]] void microSdTask(void *p) {

    // Configure 10ms interrupt.
    Timer::set(TIM2, Div_1, 7200, 100, Up);
    Timer::setTimerInterrupt(TIM2, TIM2_IRQn, Update);
    Gpio::setPin(C13, GPIO_Mode_Out_PP);

    init_spi(SPI1, 0);
    vTaskDelay(1000);

    if (f_mount(&FatFs, "0", 1) == FR_OK) {
        if (f_open(&fil, "1stfile.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE) == FR_OK) {
            if (f_puts("First string in my file\n", &fil) > 0) {
                printf("write\n");
            }
            f_close(&fil);
        }
        f_mount(0, "", 1);
    }
    // main loop
    while (1) {
        vTaskDelay(1000);
        Gpio::pinHigh(C13);
        spi_slave_enable();
        vTaskDelay(1000);
        Gpio::pinLow(C13);
        spi_slave_disable();

    }
}
