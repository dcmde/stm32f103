#ifndef TEMPLATE_MICROSDTASK_HPP
#define TEMPLATE_MICROSDTASK_HPP

#include <stm32f10x.h>

#include "FreeRTOS.h"
#include "task.h"

[[noreturn]] void microSdTask(void *p);

#endif //TEMPLATE_MICROSDTASK_HPP
