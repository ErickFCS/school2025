#include "standAloneFuncs.hpp"

extern "C" {
    #include <freertos/FreeRTOS.h>
    #include "freertos/task.h"      //para los delays (vTaskDelay)
    #include "driver/gpio.h"        //para los GPIO
    #include "driver/adc.h"
}

void adc_init(void) {
    // Configurar canal ADC1_CH0 (GPIO1) con atenuación 11 dB (voltaje medible ~0–3.3 V)
    // el canal canal ADC2_CH0 son el resto d epines, pero se rompa si usas WIFI
    adc1_config_width(ADC_WIDTH_BIT_12);                           // resolución 12 bist
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
}
