#pragma once
#include "pinControl.hpp"
#include "esp_timer.h"


class DHT22 {
private:
    int pin;
    float humidity;
    float temperature;
    uint8_t data[5] = {0};

    bool waitForLevel(int level, uint32_t timeout_us);
public:
    DHT22(int p) : pin(p), humidity(0), temperature(0) {}

    float getHumidity() const { return humidity; }
    float getTemperature() const { return temperature; }

    int8_t readSensorData();
};
