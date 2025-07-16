#pragma once
#include "pinControl.hpp"
#include "esp_timer.h"


class DHT22{
private:
    pinControl pin;
    float humidity;
    float temperature;
    unsigned char data[5];
    bool waitSignal(bool signal, unsigned long timeout);
public:
    DHT22(int pin) : pin(pin), humidity(0), temperature(0) {}
    float getHumidity(){ return humidity; }
    float getTemperature(){ return temperature; }
    char readSensorData();
};
