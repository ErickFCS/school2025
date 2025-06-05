#include "pinControl.hpp"


pinControl::pinControl(int pinNumber) : pinNumber(pinNumber), state(0) {}

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

void pinControl::setAsInput(int pull = 0) {
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
                adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
                break;
            case 2:
                adc1_config_channel_atten(ADC1_CHANNEL_1, ADC_ATTEN_DB_11);
                break;
            case 3:
                adc1_config_channel_atten(ADC1_CHANNEL_2, ADC_ATTEN_DB_11);
                break;
            case 4:
                adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_11);
                break;
            case 5:
                adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);
                break;
            case 6:
                adc1_config_channel_atten(ADC1_CHANNEL_5, ADC_ATTEN_DB_11);
                break;
            case 7:
                adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);
                break;
            case 8:
                adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_11);
                break;
            default:
                break;
        }
    } else {
        adc1_config_width(ADC_WIDTH_BIT_12);
        switch (pinNumber) {
            case 1:
                adc2_config_channel_atten(ADC2_CHANNEL_0, ADC_ATTEN_DB_11);
                break;
            case 2:
                adc2_config_channel_atten(ADC2_CHANNEL_1, ADC_ATTEN_DB_11);
                break;
            case 3:
                adc2_config_channel_atten(ADC2_CHANNEL_2, ADC_ATTEN_DB_11);
                break;
            case 4:
                adc2_config_channel_atten(ADC2_CHANNEL_3, ADC_ATTEN_DB_11);
                break;
            case 5:
                adc2_config_channel_atten(ADC2_CHANNEL_4, ADC_ATTEN_DB_11);
                break;
            case 6:
                adc2_config_channel_atten(ADC2_CHANNEL_5, ADC_ATTEN_DB_11);
                break;
            case 7:
                adc2_config_channel_atten(ADC2_CHANNEL_6, ADC_ATTEN_DB_11);
                break;
            case 8:
                adc2_config_channel_atten(ADC2_CHANNEL_7, ADC_ATTEN_DB_11);
                break;
            case 9:
                adc2_config_channel_atten(ADC2_CHANNEL_8, ADC_ATTEN_DB_11);
                break;
            case 10:
                adc2_config_channel_atten(ADC2_CHANNEL_9, ADC_ATTEN_DB_11);
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
                state = adc1_get_raw(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
                break;
            case 2:
                state = adc1_get_raw(ADC1_CHANNEL_1, ADC_ATTEN_DB_11);
                break;
            case 3:
                state = adc1_get_raw(ADC1_CHANNEL_2, ADC_ATTEN_DB_11);
                break;
            case 4:
                state = adc1_get_raw(ADC1_CHANNEL_3, ADC_ATTEN_DB_11);
                break;
            case 5:
                state = adc1_get_raw(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);
                break;
            case 6:
                state = adc1_get_raw(ADC1_CHANNEL_5, ADC_ATTEN_DB_11);
                break;
            case 7:
                state = adc1_get_raw(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);
                break;
            case 8:
                state = adc1_get_raw(ADC1_CHANNEL_7, ADC_ATTEN_DB_11);
                break;
            case 9:
                state = adc1_get_raw(ADC1_CHANNEL_8, ADC_ATTEN_DB_11);
                break;
            case 10:
                state = adc1_get_raw(ADC1_CHANNEL_9, ADC_ATTEN_DB_11);
                break;
            default:
                break;
        }
    } else {
        switch (pinNumber) {
            case 1:
                state = adc2_get_raw(ADC2_CHANNEL_0, ADC_ATTEN_DB_11);
                break;
            case 2:
                state = adc2_get_raw(ADC2_CHANNEL_1, ADC_ATTEN_DB_11);
                break;
            case 3:
                state = adc2_get_raw(ADC2_CHANNEL_2, ADC_ATTEN_DB_11);
                break;
            case 4:
                state = adc2_get_raw(ADC2_CHANNEL_3, ADC_ATTEN_DB_11);
                break;
            case 5:
                state = adc2_get_raw(ADC2_CHANNEL_4, ADC_ATTEN_DB_11);
                break;
            case 6:
                state = adc2_get_raw(ADC2_CHANNEL_5, ADC_ATTEN_DB_11);
                break;
            case 7:
                state = adc2_get_raw(ADC2_CHANNEL_6, ADC_ATTEN_DB_11);
                break;
            case 8:
                state = adc2_get_raw(ADC2_CHANNEL_7, ADC_ATTEN_DB_11);
                break;
            case 9:
                state = adc2_get_raw(ADC2_CHANNEL_8, ADC_ATTEN_DB_11);
                break;
            case 10:
                state = adc2_get_raw(ADC2_CHANNEL_9, ADC_ATTEN_DB_11);
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
