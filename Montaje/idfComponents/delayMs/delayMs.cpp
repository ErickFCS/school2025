#include "delayMs.hpp"
extern "C" {
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
}

void delayMs(int ms) {
    // Delay for the specified number of milliseconds
    vTaskDelay(pdMS_TO_TICKS(ms));
}