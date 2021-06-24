#include <FreeRTOS.h>
#include <ff.h>
#include <gpio.hpp>
#include <misc.h>
#include <spi.h>
#include <i2c.h>
#include <task.h>
#include <task/microSdTask.hpp>
#include <timer.hpp>
#include "diskio-spi-wrapper.h"
#include <bme280.h>
#include <mpu6050.h>
#include <cstring>
#include <cstdio>

FATFS FatFs;
FIL fil;
SPI_t spi_bme;
I2C_t i2c;

uint8_t interfaceReadRegister(uint8_t register_address) {
    return I2C_ReadByte(&i2c, BME280_I2C_ADDR_0x76, register_address);
}

void interfaceReadRegisters(uint8_t register_address, uint8_t *buffer, uint8_t size) {
    I2C_ReadBuffer(&i2c, BME280_I2C_ADDR_0x76, register_address, buffer, size);
}

void interfaceWriteRegister(uint8_t register_address, uint8_t value) {
    I2C_WriteByte(&i2c, BME280_I2C_ADDR_0x76, register_address, value);
}

ERROR_t ReadBuffer(uint8_t reg_addr, uint8_t *buffer, uint8_t size) {
    I2C_ReadBuffer(&i2c, MPU6050_I2C_ADDR_0x68, reg_addr, buffer, size);
    return NO_ERROR;
}

ERROR_t WriteBuffer(uint8_t reg_addr, uint8_t *buffer, uint8_t size) {
    I2C_WriteBuffer(&i2c, MPU6050_I2C_ADDR_0x68, reg_addr, buffer, size);
    return NO_ERROR;
}

[[noreturn]] void microSdTask(void *p) {
    SPI_t spi;
    BME280_t bme;
    char buffer[50];
    MPU6050_t mpu6050;
    mpu6050.ReadBuffer = &ReadBuffer;
    mpu6050.WriteBuffer = &WriteBuffer;

    i2c.speed = 200000;
    i2c.I2Cx = I2C1;
    i2c.own_dev_addr = 0x02;

    I2C_Initialization(&i2c);

    MPU6050_Init(&mpu6050);
    MPU6050_ReadAccel(&mpu6050);
    MPU6050_ReadGyro(&mpu6050);

    printf("%i %i %i\n", mpu6050.accel[0], mpu6050.accel[1], mpu6050.accel[2]);
    printf("%i %i %i\n", mpu6050.gyro[0], mpu6050.gyro[1], mpu6050.gyro[2]);

    // Configure 10ms interrupt.
    Timer::set(TIM2, Div_1, 7200, 100, Up);
    Timer::setTimerInterrupt(TIM2, TIM2_IRQn, Update);
    Gpio::setPin(C13, GPIO_Mode_Out_PP);

//    spi.SPIx = SPI2;
//    spi.GPIOx = GPIOB;
//    spi.mode = MASTER;
//    spi.NSS_PIN = GPIO_Pin_12;
//
//    spi_bme = spi;
//    spi_bme.NSS_PIN = GPIO_Pin_10;
//
//    SPI_Initialization(&spi);
//    SPI_InitPin(&spi);
//    SPI_InitPin(&spi_bme);
//
//    spi_miroSd = &spi;

    bme.initStruct.OVS_H = OVS_H_1;
    bme.initStruct.OVS_P = OVS_P_1;
    bme.initStruct.OVS_T = OVS_T_1;
    bme.initStruct.MODE = MODE_NORMAL;

    bme.ReadRegister = &interfaceReadRegister;
    bme.ReadRegisters = &interfaceReadRegisters;
    bme.WriteRegister = &interfaceWriteRegister;

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
