#ifndef PINCONTROL_HPP
#define PINCONTROL_HPP
extern "C"{
    #include "freertos/FreeRTOS.h"
    #include "driver/gpio.h"
    #include "driver/adc.h"
}
enum class pinTypes{
    OUTPUT,
    INPUT,
    INPUT_UP,   //input with pull up
    INPUT_DOWN, //input with pull down
    ANALOG_INPUT,
    ANALOG_OUTPUT
};

#define DELAYMS(x) vTaskDelay(( x + (portTICK_PERIOD_MS - 1) )/portTICK_PERIOD_MS);

bool pinAs(int pin, pinTypes mode);
bool setPin(int pin, int state);
bool getDigital(int pin);
int getAnalog(int gpio);

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
        void setAsInput(int pull=0);
        int readState();
        void setAsAnalogInput(int pull);
        int readAnalogState();
        void configure(gpio_config_t io_conf);
};

#endif // PINCONTROL_HPP
