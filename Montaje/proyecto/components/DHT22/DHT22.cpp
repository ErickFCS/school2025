#include "DHT22.hpp"
#include "esp_timer.h"
#include <cstring>

#define TAG "DHT22"

bool DHT22::waitForLevel(int level, uint32_t timeout_us) {
    int64_t start = esp_timer_get_time();
    while (getDigital(pin) != level) {
        if ((esp_timer_get_time() - start) > timeout_us) return false;
    }
    return true;
}

int8_t DHT22::readSensorData() {
    memset(data, 0, sizeof(data));

    // Start signal
    pinAs(pin, pinTypes::OUTPUT);
    setPin(pin, 0);
    vTaskDelay(pdMS_TO_TICKS(2)); // al menos 1 ms, mejor 2 para asegurarse
    setPin(pin, 1);
    esp_rom_delay_us(30); // Espera 20–40us antes de cambiar a input

    pinAs(pin, pinTypes::INPUT_UP); // DHT responderá en el mismo pin

    // Esperar respuesta del sensor
    if (!waitForLevel(0, 100)) return -1;  // espera LOW (80us)
    if (!waitForLevel(1, 100)) return -2;  // espera HIGH (80us)

    // Comienza la lectura de 40 bits
    for (int i = 0; i < 40; ++i) {
        if (!waitForLevel(0, 70)) return -3; // espera LOW (50us)
        if (!waitForLevel(1, 70)) return -4; // espera HIGH (variable duración)

        int64_t start = esp_timer_get_time();
        while (getDigital(pin) == 1) {
            if ((esp_timer_get_time() - start) > 100) break; // evitar bloqueo
        }

        int64_t pulseDuration = esp_timer_get_time() - start;
        int byteIndex = i / 8;
        int bitIndex = 7 - (i % 8);

        if (pulseDuration > 50) {
            data[byteIndex] |= (1 << bitIndex); // Bit = 1
        }
        // else Bit = 0 (por defecto, ya está en 0)
    }

    // Verificación de checksum
    uint8_t sum = data[0] + data[1] + data[2] + data[3];
    if (data[4] != sum) return -5;

    humidity = ((data[0] << 8) | data[1]) / 10.0f;
    temperature = ((data[2] << 8) | data[3]) / 10.0f;

    return 0; // éxito
}
