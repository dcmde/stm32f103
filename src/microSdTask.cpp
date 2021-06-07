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
#include <cstring>
#include <cstdio>

FATFS FatFs;
FIL fil;
SPI_t spi_bme;

uint8_t interfaceReadRegister(uint8_t register_address) {
    uint8_t buffer[2];
    buffer[0] = register_address | 0x80;
    buffer[1] = 0xFE;
    SPI_SlaveEnable(&spi_bme);
    SPI_BufferSendReceive(&spi_bme, buffer, 2);
    SPI_SlaveDisable(&spi_bme);
    return buffer[1];
}

void interfaceReadRegisters(uint8_t register_address, uint8_t *buffer, uint8_t size) {
    uint8_t temp[size + 1];
    temp[0] = register_address | 0x80;
    memcpy(temp + 1, buffer, size);
    SPI_SlaveEnable(&spi_bme);
    SPI_BufferSendReceive(&spi_bme, temp, size);
    memcpy(buffer, temp + 1, size);
    SPI_SlaveDisable(&spi_bme);
}

void interfaceWriteRegisters(uint8_t register_address, uint8_t value) {
    uint8_t buffer[2];
    buffer[0] = register_address & ~0x80;
    buffer[1] = value;
    SPI_SlaveEnable(&spi_bme);
    SPI_BufferSendReceive(&spi_bme, buffer, 2);
    SPI_SlaveDisable(&spi_bme);
}

[[noreturn]] void microSdTask(void *p) {
    SPI_t spi;
    BME280_t bme;
    char buffer[50];

    // Configure 10ms interrupt.
    Timer::set(TIM2, Div_1, 7200, 100, Up);
    Timer::setTimerInterrupt(TIM2, TIM2_IRQn, Update);
    Gpio::setPin(C13, GPIO_Mode_Out_PP);

    spi.SPIx = SPI2;
    spi.GPIOx = GPIOB;
    spi.mode = MASTER;
    spi.NSS_PIN = GPIO_Pin_12;

    spi_bme = spi;
    spi_bme.NSS_PIN = GPIO_Pin_10;

    SPI_Initialization(&spi);
    SPI_InitPin(&spi);
    SPI_InitPin(&spi_bme);

    spi_miroSd = &spi;

    printf("SPI OK\n");

    bme.initStruct.OVS_H = OVS_H_1;
    bme.initStruct.OVS_P = OVS_P_1;
    bme.initStruct.OVS_T = OVS_T_1;
    bme.initStruct.MODE = MODE_NORMAL;

    bme.ReadRegister = &interfaceReadRegister;
    bme.ReadRegisters = &interfaceReadRegisters;
    bme.WriteRegister = &interfaceWriteRegisters;

    printf("Init BME\n");
    if (BME280_Init(&bme)) {
        printf("Init BME KO\n");
        while (1);
    } else {
        printf("Init BME OK\n");
    }

    BME280_ReadConfigurationParameters(&bme);
    BME280_ReadSensors(&bme);
    printf("Temp %i\n", (int) bme.sensorsValues.Temp);

    vTaskDelay(100);

    for (uint32_t i = 0; i < 1000; ++i) {
        vTaskDelay(1000);
        BME280_ReadSensors(&bme);
        printf("Temp %i\n", (int) bme.sensorsValues.Temp);
        printf("Pres %i\n", (int) bme.sensorsValues.Pres);
        printf("Hum %i\n", (int) bme.sensorsValues.Hum);
    }

//    if (f_mount(&FatFs, "0", 1) == FR_OK) {
//        if (f_open(&fil, "data.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE) == FR_OK) {
//            if (f_puts("Temp Hum Pres\n", &fil) < 0) {
//                printf("Cannot print to file\n");
//            }
//            for (uint32_t i = 0; i < 10; ++i) {
//
//                vTaskDelay(5000);
//                BME280_ReadSensors(&bme);
//                sprintf(buffer, "%li %lui %lui\n",
//                        bme.sensorsValues.Temp,
//                        bme.sensorsValues.Hum,
//                        bme.sensorsValues.Pres);
//                if (f_puts(buffer, &fil) < 0) {
//                    f_close(&fil);
//                    printf("Print error\n");
//                    break;
//                }
//                printf(buffer);
//            }
//        }
//        f_mount(0, "", 1);
//    }

    // main loop
    while (1) {
        vTaskDelay(1000);
        Gpio::pinHigh(C13);
        vTaskDelay(1000);
        Gpio::pinLow(C13);
    }
}
