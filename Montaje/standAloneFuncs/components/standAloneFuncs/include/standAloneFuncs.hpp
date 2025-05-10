#pragma once

#include "hal/gpio_types.h"         //para los enums de mierdas de los GPIO que obliga a usar

//defines numericos
#define HIGH 1
#define LOW 0


//defines funcionales
#define delayMs(ms) (vTaskDelay( ms / portTICK_PERIOD_MS))
#define dWrite(pin,level) (gpio_set_level(static_cast<gpio_num_t>(pin), level))
#define dRead(pin) (gpio_get_level(pin)

//funciones
void adc_init(void);
