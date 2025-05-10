#ifndef HDT22
#define HDT22

class DHT22
{
private:
    int pin;
    float humidity;
    float temperature;
    unsigned char data[5];
    bool waitSignal(bool signal, unsigned long timeout)
    {
        long deadLine = micros() + timeout;
        while (digitalRead(this->pin) != signal)
        {
            if (micros() > deadLine)
                // return -1; // Timeout
                return false; // Timeout
        }
        // return micros() - deadLine; // Return the time it took to get the signal
        return true;
    }
public:
    char readSensorData();
    float getHumidity() { return humidity; }
    float getTemperature() { return temperature; }
    DHT22(int pin) : pin(pin), humidity(0), temperature(0) {}
};

char DHT22::readSensorData()
{
    digitalWrite(pin, HIGH); // Prevent start
    pinMode(pin, OUTPUT);    // Set pin to output mode
    digitalWrite(pin, LOW);  // Start signal
    delay(1);                // Wait for 1 milisecond
    pinMode(pin, INPUT);     // Set pin to input mode and end signal

    if (!waitSignal(LOW, 45))  // Wait for lower signal (40us)
        return -1;             // Timeout
    if (!waitSignal(HIGH, 85)) // Wait for higher signal (80us)
        return -2;             // Timeout
    if (!waitSignal(LOW, 85))  // Wait for lower signal (80us)
        return -3;             // Timeout

    unsigned long highStart; // Start time of the high signal
    for (char i = 0; i < 5; i++)
    {
        for (char ii = 0; ii < 8; ii++)
        {
            if (!waitSignal(HIGH, 55))       // Wait for higher signal (50us)
                return -4;                   // Timeout
            highStart = micros();            // Start time of the high signal
            if (!waitSignal(LOW, 80))        // Wait for lower signal (70us)
                return -5;                   // Timeout
            if (micros() - highStart < 40)   // If the high signal was less than 28us
                data[i] &= ~(1 << (7 - ii)); // Set the bit to 0
            else
                data[i] |= (1 << (7 - ii)); // Set the bit to 1
        }
    }
    if ((unsigned char)(data[0] + data[1] + data[2] + data[3]) != data[4]) // Checksum
        return -6;                                                // Checksum error
    humidity = data[0] + data[1] / 10.0f;                         // Humidity
    temperature = data[2] + data[3] / 10.0f;                      // Temperature
    return 0;                                                     // Success
}

#endif // HDT22
