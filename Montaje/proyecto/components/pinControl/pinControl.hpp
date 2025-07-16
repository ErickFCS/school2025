#ifndef PINCONTROL_HPP
#define PINCONTROL_HPP
extern "C"{
    #include "freertos/FreeRTOS.h"
    #include "driver/gpio.h"
    #include "driver/adc.h"
}

#define DELAYMS(x) vTaskDelay(( x + (portTICK_PERIOD_MS - 1) )/portTICK_PERIOD_MS);

class pinControl {
    private:
        int pinNumber;
        int state;
    public:
        pinControl(int pinNumber);
        int getPinNumber();
        void setPinNumber(int pinNumber);
        void setAsOutput();
        int getState();
        void set(int state);
        void setHigh();
        void setLow();
        void toggleState();
        void setAsInput(int pull);
        int readState();
        void setAsAnalogInput(int pull);
        int readAnalogState();
        void configure(gpio_config_t io_conf);
};

#endif // PINCONTROL_HPP
