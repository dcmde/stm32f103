#ifndef TEMPLATE_STM32TASKS_HPP
#define TEMPLATE_STM32TASKS_HPP

#include <stm32f10x.h>

#include "FreeRTOS.h"
#include "task.h"

struct Parameters {
    uint32_t id;
    TickType_t delay;
};

[[noreturn]] void my_task(void *p);

#endif //TEMPLATE_STM32TASKS_HPP
