#include <FreeRTOS.h>
#include <ff.h>
#include <gpio.hpp>
#include <misc.h>
#include <spi.h>
#include <task.h>
#include <task/microSdTask.hpp>
#include <timer.hpp>
#include "diskio-spi-wrapper.h"
#include <bme280.h>

FATFS FatFs;
FIL fil;

[[noreturn]] void microSdTask(void *p) {
    SPI_t spi;

    // Configure 10ms interrupt.
    Timer::set(TIM2, Div_1, 7200, 100, Up);
    Timer::setTimerInterrupt(TIM2, TIM2_IRQn, Update);
    Gpio::setPin(C13, GPIO_Mode_Out_PP);

    spi.SPIx = SPI2;
    spi.GPIOx = GPIOB;
    spi.mode = MASTER;
    spi.NSS_PIN = GPIO_Pin_12;
    init_spi(&spi);
    init_spi_pin(&spi);

    spi_miroSd = &spi;

    vTaskDelay(1000);

    if (f_mount(&FatFs, "0", 1) == FR_OK) {
        if (f_open(&fil, "stfile.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE) == FR_OK) {
            if (f_puts("First string in my file\n", &fil) > 0) {}
            f_close(&fil);
        }
        f_mount(0, "", 1);
    }
    // main loop
    while (1) {
        vTaskDelay(1000);
        Gpio::pinHigh(C13);
        vTaskDelay(1000);
        Gpio::pinLow(C13);

    }
}
