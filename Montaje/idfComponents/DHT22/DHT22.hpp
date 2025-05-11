#ifndef HDT22
#define HDT22

class DHT22
{
private:
    int pin;
    float humidity;
    float temperature;
    unsigned char data[5];
public:
    bool waitSignal(bool signal);
    DHT22(int pin);
    void init();
    char readSensorData();
    float getHumidity();
    float getTemperature();
};

#endif // HDT22
