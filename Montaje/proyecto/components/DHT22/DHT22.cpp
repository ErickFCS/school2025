#include "DHT22.hpp"
#include "esp_timer.h"

#define TAG "DHT22"

char DHT22::readSensorData(){
    pin.setHigh(); // Prevent start
    pin.setAsOutput();    // Set pin to output mode
    pin.setLow();  // Start signal
    DELAYMS(1);                // Wait for 1 milisecond
    pin.setAsInput(0);     // Set pin to input mode and end signal

    if (!waitSignal(0, 45))  // Wait for lower signal (40us)
        return -1;             // Timeout
    if (!waitSignal(1, 85)) // Wait for higher signal (80us)
        return -2;             // Timeout
    if (!waitSignal(0, 85))  // Wait for lower signal (80us)
        return -3;             // Timeout

    unsigned long highStart; // Start time of the high signal
    for (int_fast8_t i = 0; i < 5; i++)
    {
        for (int_fast8_t ii = 0; ii < 8; ii++)
        {
            if (!waitSignal(1, 55))       // Wait for higher signal (50us)
                return -4;                   // Timeout
            highStart = esp_timer_get_time();            // Start time of the high signal
            if (!waitSignal(0, 80))        // Wait for lower signal (70us)
                return -5;                   // Timeout
            if (esp_timer_get_time() - highStart < 40)   // If the high signal was less than 28us
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
