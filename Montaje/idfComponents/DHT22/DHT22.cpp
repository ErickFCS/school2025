#include "DHT22.hpp"
#include "delayMs.hpp"
extern "C" {
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "esp_timer.h"
}

DHT22::DHT22(int pin) : humidity(0.0), temperature(0.0) {
    pin = pinControl(pin);
    pin.setAsInput(1);
}

bool DHT22::waitSignal(bool signal)
{
    uint32_t startTime = esp_timer_get_time();
    while (pin.readState() != signal) {
        if (startTime + 1000000 < esp_timer_get_time()) {
            return false;  // Timeout
        }
    }
    return true;
}