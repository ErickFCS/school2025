#include "st7789.hpp"
#include "esp_log.h"
#include "wifi.hpp"

#define TAG "main"

#define DEFAULT_SSID "MAL-config-net"
#define DEFAULT_PASSWORD "configuration"

extern "C" void app_main() {
    delayMS(5050);
    ESP_LOGI(TAG,"begining delay ended");
    st7789* pantalla=st7789::getInstance();

    wifi::init();
    wifi::connect(DEFAULT_SSID,DEFAULT_PASSWORD);

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

}
