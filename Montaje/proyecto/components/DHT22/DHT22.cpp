#include "DHT22.hpp"
#include "esp_timer.h"
#include <cstring>

#define TAG "DHT22"

bool DHT22::waitForLevel(int level, uint32_t timeout_us) {
    int64_t start = esp_timer_get_time();
    while (getDigital(pin) != level)
        if ((esp_timer_get_time() - start) > timeout_us) return false;
    return true;
}

int8_t DHT22::readSensorData() {
    // Start signal
    setPin(pin, 1);
    pinAs(pin, pinTypes::OUTPUT);
    setPin(pin, 0);
    //vTaskDelay(pdMS_TO_TICKS(1)); // al menos 1 ms, mejor 2 para asegurarse
    esp_rom_delay_us(1000);
    pinAs(pin, pinTypes::INPUT);

    // Esperar respuesta del sensor
    if (!waitForLevel(0, 45)) return -1;  // espera 0 (80us)
    if (!waitForLevel(1, 85)) return -2;  // espera 1 (80us)
    if (!waitForLevel(0, 85)) return -3;  // espera 0 (80us)

    uint64_t highStart;
    for (uint8_t i = 0; i < 5; i++)for (uint8_t ii = 0; ii < 8; ii++){
        if(!waitForLevel(1,55))                 // Wait for higher signal (50us)
            return -4;                          // Timeout
        highStart = esp_timer_get_time();       // Start time of the high signal
        if(!waitForLevel(0,80))                 // Wait for lower signal (70us)
            return -5;                          // Timeout
        if(esp_timer_get_time()-highStart<40)   // If the high signal was less than 28us
            data[i]&= ~(1<< (7 - ii));          // Set the bit to 0
        else data[i] |= (1 << (7 - ii));        // Set the bit to 1
    }
    
    // Verificación de checksum
    if (data[4] != data[0] + data[1] + data[2] + data[3]) return -5;

    humidity = ((data[0] << 8) | data[1]) / 10.0f;
    temperature = ((data[2] << 8) | data[3]) / 10.0f;

    return 0; // éxito
}
