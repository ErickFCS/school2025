#ifndef HDT22
#define HDT22

#include "pinControl.hpp"

class DHT22
{
private:
    pinControl pin;
    float humidity;
    float temperature;
    unsigned char data[5];
public:
    bool waitSignal(bool signal);
    DHT22(int pin);
    char readSensorData();
    float getHumidity();
    float getTemperature();
};

#endif // HDT22
