cmake_minimum_required(VERSION 3.10)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Prevent error from CLion
SET(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Set compiler for ARM
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
set(CMAKE_OBJCOPY "arm-none-eabi-objcopy")

project(template C CXX ASM)

# Header files directory
include_directories(include
        lib/FreeRTOS-Kernel/include
        lib/drivers/include/ff11
        lib/FreeRTOS-Kernel/portable/GCC/ARM_CM3/
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/inc
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/CMSIS/CM3/CoreSupport
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x
        lib/stm32f1_hal/include
        lib/drivers/include)

# Source files directory
SET(USER_SOURCES
        src/main.cpp
        src/heap_4.c
        src/interrupts.cpp
        src/microSdTask.cpp
        src/timerTask.cpp
        lib/stm32f1_hal/src/stm32f103_dbg.c
        lib/stm32f1_hal/src/gpio.cpp
        lib/stm32f1_hal/src/timer.cpp
        lib/stm32f1_hal/src/spi.c
        lib/stm32f1_hal/src/i2c.c
        lib/drivers/src/ff11/ff.c
        lib/drivers/src/ff11/diskio.c
        lib/drivers/src/ff11/diskio-spi-wrapper.c
        lib/drivers/src/bme280.c
        lib/drivers/src/mpu6050.c
        lib/FreeRTOS-Kernel/croutine.c
        lib/FreeRTOS-Kernel/event_groups.c
        lib/FreeRTOS-Kernel/list.c
        lib/FreeRTOS-Kernel/queue.c
        lib/FreeRTOS-Kernel/stream_buffer.c
        lib/FreeRTOS-Kernel/tasks.c
        lib/FreeRTOS-Kernel/timers.c
        lib/FreeRTOS-Kernel/portable/GCC/ARM_CM3/port.c
        )

SET(SPL_SOURCES
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/misc.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_adc.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_can.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_cec.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_crc.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dac.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dbgmcu.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dma.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_i2c.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_iwdg.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_sdio.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_wwdg.c
        )

SET(CMSIS_SOURCES
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c
        lib/STM32F10x_StdPeriph_Lib_V3.3.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/TrueSTUDIO/startup_stm32f10x_md.s)

# C flags with and without printf
SET(COMMON_FLAGS "-g -O1 -Wall -DSTM32F103x6 -DUSE_STDPERIPH_DRIVER -mcpu=cortex-m3 -mthumb -mthumb-interwork -mfpu=vfp -msoft-float -mfix-cortex-m3-ldrd -ffreestanding -lc -u _printf_float -flto -specs=nano.specs -specs=nosys.specs")
#SET(COMMON_FLAGS "-g -O1 -Wall -DSTM32F103x6 -DUSE_STDPERIPH_DRIVER -mcpu=cortex-m3 -mthumb -mthumb-interwork -mfpu=vfp -msoft-float -mfix-cortex-m3-ldrd -ffreestanding -lc -flto -specs=nano.specs -specs=nosys.specs")

set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -std=gnu99")

# Search for the SPL and create linker flag.
if (IS_DIRECTORY lib/STM32F10x_StdPeriph_Lib_V3.3.0)
    SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--no-wchar-size-warning,--gc-sections,-M=binary.map,-T./lib/STM32F10x_StdPeriph_Lib_V3.3.0/Project/STM32F10x_StdPeriph_Template/TrueSTUDIO/STM3210B-EVAL/stm32_flash.ld")
elseif (IS_DIRECTORY ../lib/STM32F10x_StdPeriph_Lib_V3.3.0)
    SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--no-wchar-size-warning,--gc-sections,-M=binary.map,-T../lib/STM32F10x_StdPeriph_Lib_V3.3.0/Project/STM32F10x_StdPeriph_Template/TrueSTUDIO/STM3210B-EVAL/stm32_flash.ld")
else ()
    message("Cannot find STM32F10x_StdPeriph_Lib_V3.3.0 folder")
endif ()

# Libraries
add_library(SPL ${SPL_SOURCES})
add_library(CMSIS ${CMSIS_SOURCES})

# Executable
add_executable(${PROJECT_NAME}.elf ${USER_SOURCES})
target_link_libraries(${PROJECT_NAME}.elf SPL CMSIS)

# Create build directory.
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/build/)

# Generate binary.
set(HEX_FILE ${PROJECT_SOURCE_DIR}/bin/build/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_SOURCE_DIR}/bin/build/${PROJECT_NAME}.bin)

# Custom commands.
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE} \nBuilding ${BIN_FILE}")

add_custom_target(flash
        COMMAND ../script/script.zsh
        COMMENT "Flashing the target processor...")

add_custom_command(TARGET flash POST_BUILD COMMENT "Flashing finished!")
