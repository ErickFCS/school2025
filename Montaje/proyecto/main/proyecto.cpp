#include "pinControl.hpp"
#include "st7789.hpp"
#include "esp_log.h"
#include "wifi.hpp"
#include "http.hpp"
#include "DHT22.hpp"
#include <string>

#define TAG "main"

#define DEFAULT_SSID "MAL-config-net"
#define DEFAULT_PASSWORD "configuration"
#define DEFAULT_SSID "Fibertel WiFi102 2.4GHz"
#define DEFAULT_PASSWORD "01431224094"
#define DHT_PIN 14

void blink(){
    pinAs(3,pinTypes::OUTPUT);
    pinAs(4,pinTypes::INPUT);
    while (true) {
        setPin(3,1);
        ESP_LOGI(TAG, "Pin 3 nivel: %d", getDigital(3));
        ESP_LOGI(TAG, "Pin 4 nivel: %d", getDigital(4));
        vTaskDelay(pdMS_TO_TICKS(1000));
        setPin(3,0);
        ESP_LOGI(TAG, "Pin 3 nivel: %d", getDigital(3));
        ESP_LOGI(TAG, "Pin 4 nivel: %d", getDigital(4));
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

extern "C" void app_main() {
    adc1_config_width(ADC_WIDTH_BIT_12);    //resolucion de los pines analogicos
    delayMS(5050);
    //blink();
    
    DHT22 humedad(DHT_PIN);
    std::string body;
    pinAs(1,pinTypes::INPUT);
    pinAs(14,pinTypes::OUTPUT);
    setPin(14,1);
    delayMS(6060);
    setPin(14,0);
    delayMS(6060);

    wifi::init();
    wifi::connect(DEFAULT_SSID,DEFAULT_PASSWORD);
    HttpClient peticiones("https://quesito.requestcatcher.com/test");
    peticiones.set_method(Method::POST);
    std::string respuesta;
    while (1){
        int8_t status = humedad.readSensorData();
        if(status!=0)
            ESP_LOGW(TAG,"humidity sensor error. code:%d",status);

        ESP_LOGI(TAG, "Humedad: %.1f %% | Temperatura: %.1f °C | PPM: %d ", humedad.getHumidity(), humedad.getTemperature(),getAnalog(1));
        body=std::to_string(humedad.getTemperature());
        peticiones.set_body(body);
        peticiones.perform(respuesta);
        delayMS(3000);
    }
#if 0
    ESP_LOGI(TAG,"begining delay ended");
    st7789* pantalla=st7789::getInstance();
    while(1){
        pantalla->fillScreen(rgb565(255,0,0));
        pantalla->render();
        ESP_LOGI(TAG,"red");
        delayMS(5000);
        pantalla->fillScreen(rgb565(0,255,0));
        pantalla->render();
        ESP_LOGI(TAG,"green");
        delayMS(5000);
        pantalla->fillScreen(rgb565(0,0,255));
        pantalla->render();
        ESP_LOGI(TAG,"blue");
        delayMS(5000);
    }
#endif


}
