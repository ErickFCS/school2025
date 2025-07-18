#include "pinControl.hpp"
#include "hal/adc_types.h"
#include "esp_log.h"

// Rango válido para ADC1 en ESP32‑S3
static constexpr int ADC1_GPIO_MIN = 1;
static constexpr int ADC1_GPIO_MAX = 10;

int getAnalog(int gpio){
    if (gpio < ADC1_GPIO_MIN || gpio > ADC1_GPIO_MAX) {
        ESP_LOGE("analogRead", "GPIO %d no es valido para ADC1 (de %d a %d)",gpio, ADC1_GPIO_MIN, ADC1_GPIO_MAX);
        return -1;
    }
    adc1_channel_t channel = static_cast<adc1_channel_t>(gpio - ADC1_GPIO_MIN);
    adc1_config_channel_atten(channel, ADC_ATTEN_DB_12); // Hasta 3.3 V
    return adc1_get_raw(channel);
}

bool pinAs(int pin, pinTypes mode) {
    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = 1ULL << pin;
    io_conf.intr_type = GPIO_INTR_DISABLE;

    switch (mode) {
        case pinTypes::OUTPUT:
            io_conf.mode = GPIO_MODE_INPUT_OUTPUT;
            io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
            io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
            break;

        case pinTypes::INPUT:
            io_conf.mode = GPIO_MODE_INPUT;
            io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
            io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
            break;

        case pinTypes::INPUT_UP:
            io_conf.mode = GPIO_MODE_INPUT;
            io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
            io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
            break;

        case pinTypes::INPUT_DOWN:
            io_conf.mode = GPIO_MODE_INPUT;
            io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
            io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
            break;

        default:
            return false; // Tipo no soportado
    }

    return gpio_config(&io_conf) == ESP_OK;
}

bool setPin(int pin, int state) {
    return gpio_set_level((gpio_num_t)pin, state) == ESP_OK;
}

bool getDigital(int pin) {
    return gpio_get_level((gpio_num_t)pin);
}

pinControl::pinControl(int pinNumber) : pinNumber(pinNumber), state(0) {gpio_reset_pin((gpio_num_t)pinNumber);}

int pinControl::getPinNumber() {
    return pinNumber;
}

void pinControl::setPinNumber(int pinNumber) {
    this->pinNumber = pinNumber;
}

void pinControl::setAsOutput() {
    gpio_set_direction((gpio_num_t)pinNumber, GPIO_MODE_OUTPUT);
}

int pinControl::getState() {
    return state;
}

void pinControl::set(int state) {
    this->state = state;
    gpio_set_level((gpio_num_t)pinNumber, state);
}

void pinControl::setHigh() {
    set(1);
}

void pinControl::setLow() {
    set(0);
}

void pinControl::toggleState() {
    set(!state);
}

void pinControl::setAsInput(int pull) {
    /*
    pullup => pull = 1
    pulldown => pull = -1
    no pull => pull = 0
    */
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << pinNumber);
    if (pull == 1){
        io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
        io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    } else if (pull == -1) {
        io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
        io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
    } else {
        io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
        io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    }
    gpio_config(&io_conf);
}

int pinControl::readState() {
    state = gpio_get_level((gpio_num_t)pinNumber);
    return state;
}

void pinControl::setAsAnalogInput(int pull) {
    if(pinNumber < 11){
        adc1_config_width(ADC_WIDTH_BIT_12);
        switch (pinNumber) {
            case 1:
                adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_12);
                break;
            case 2:
               adc1_config_channel_atten(ADC1_CHANNEL_1, ADC_ATTEN_DB_12);
                break;
            case 3:
                adc1_config_channel_atten(ADC1_CHANNEL_2, ADC_ATTEN_DB_12);
                break;
            case 4:
                adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_12);
                break;
            case 5:
                adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_12);
                break;
            case 6:
                adc1_config_channel_atten(ADC1_CHANNEL_5, ADC_ATTEN_DB_12);
                break;
            case 7:
                adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_12);
                break;
            case 8:
                adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_12);
                break;
            default:
                break;
        }
    } else {
        adc1_config_width(ADC_WIDTH_BIT_12);
        switch (pinNumber) {
            case 1:
                adc2_config_channel_atten(ADC2_CHANNEL_0, ADC_ATTEN_DB_12);
                break;
            case 2:
                adc2_config_channel_atten(ADC2_CHANNEL_1, ADC_ATTEN_DB_12);
                break;
            case 3:
                adc2_config_channel_atten(ADC2_CHANNEL_2, ADC_ATTEN_DB_12);
                break;
            case 4:
                adc2_config_channel_atten(ADC2_CHANNEL_3, ADC_ATTEN_DB_12);
                break;
            case 5:
                adc2_config_channel_atten(ADC2_CHANNEL_4, ADC_ATTEN_DB_12);
                break;
            case 6:
                adc2_config_channel_atten(ADC2_CHANNEL_5, ADC_ATTEN_DB_12);
                break;
            case 7:
                adc2_config_channel_atten(ADC2_CHANNEL_6, ADC_ATTEN_DB_12);
                break;
            case 8:
                adc2_config_channel_atten(ADC2_CHANNEL_7, ADC_ATTEN_DB_12);
                break;
            case 9:
                adc2_config_channel_atten(ADC2_CHANNEL_8, ADC_ATTEN_DB_12);
                break;
            case 10:
                adc2_config_channel_atten(ADC2_CHANNEL_9, ADC_ATTEN_DB_12);
                break;
            default:
                break;
        }
    }
}

int pinControl::readAnalogState() {
    if(pinNumber < 11){
        switch (pinNumber) {
            case 1:
                state = adc1_get_raw(ADC1_CHANNEL_0);
                break;
            case 2:
                state = adc1_get_raw(ADC1_CHANNEL_1);
                break;
            case 3:
                state = adc1_get_raw(ADC1_CHANNEL_2);
                break;
            case 4:
                state = adc1_get_raw(ADC1_CHANNEL_3);
                break;
            case 5:
                state = adc1_get_raw(ADC1_CHANNEL_4);
                break;
            case 6:
                state = adc1_get_raw(ADC1_CHANNEL_5);
                break;
            case 7:
                state = adc1_get_raw(ADC1_CHANNEL_6);
                break;
            case 8:
                state = adc1_get_raw(ADC1_CHANNEL_7);
                break;
            default:
                break;
        }
    } else {
        switch (pinNumber) {
            case 1:
                adc2_get_raw(ADC2_CHANNEL_0, ADC_WIDTH_BIT_12, &state);
                break;
            case 2:
                adc2_get_raw(ADC2_CHANNEL_1, ADC_WIDTH_BIT_12, &state);
                break;
            case 3:
                adc2_get_raw(ADC2_CHANNEL_2, ADC_WIDTH_BIT_12, &state);
                break;
            case 4:
                adc2_get_raw(ADC2_CHANNEL_3, ADC_WIDTH_BIT_12, &state);
                break;
            case 5:
                adc2_get_raw(ADC2_CHANNEL_4, ADC_WIDTH_BIT_12, &state);
                break;
            case 6:
                adc2_get_raw(ADC2_CHANNEL_5, ADC_WIDTH_BIT_12, &state);
                break;
            case 7:
                adc2_get_raw(ADC2_CHANNEL_6, ADC_WIDTH_BIT_12, &state);
                break;
            case 8:
                adc2_get_raw(ADC2_CHANNEL_7, ADC_WIDTH_BIT_12, &state);
                break;
            case 9:
                adc2_get_raw(ADC2_CHANNEL_8, ADC_WIDTH_BIT_12, &state);
                break;
            case 10:
                adc2_get_raw(ADC2_CHANNEL_9, ADC_WIDTH_BIT_12, &state);
                break;
            default:
                break;
        }
    }
    return state;
}

void pinControl::configure(gpio_config_t io_conf) {
    gpio_config(&io_conf);
}
