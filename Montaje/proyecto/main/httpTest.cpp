#include "st7789.hpp"
#include "esp_log.h"
#include "wifi.hpp"
#include "http.hpp"

#define TAG "main"

#define DEFAULT_SSID "MAL-config-net"
#define DEFAULT_PASSWORD "configuration"

extern "C" void app_main() {
    delayMS(5050);

    wifi::init();
    wifi::connect(DEFAULT_SSID,DEFAULT_PASSWORD);
    HttpClient peticiones("https://quesito.requestcatcher.com/test");
    peticiones.set_method(Method::GET);
    std::string respuesta;
    while (1){
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
