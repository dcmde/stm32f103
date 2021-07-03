#include <cstdint>
#include "task/comTask.hpp"

[[noreturn]] void comTask(void *p) {
    int8_t speed = 0;

    refQueue = xQueueCreate(1, sizeof(speed));

    while (1) {
        ++speed;
        xQueueSend(refQueue, (void *) &speed, (TickType_t) 0);
        vTaskDelay(50);
    }
}