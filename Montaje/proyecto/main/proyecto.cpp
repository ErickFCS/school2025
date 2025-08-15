#include <cstddef>
#include "pinControl.hpp"
#include "st7789.hpp"
#include "esp_log.h"
#include "wifi.hpp"
#include "http.hpp"
#include "DHT22.hpp"
#include <string>
#include "nvs_flash.h"
#include "nvs.h"


/*
 * peticion POST a /api/devices/sign y se obtiene un objeto JSON con dos campos
 * recibe: {id:[INT],password:[STRING]}
 * peticion PUT a /api/devices/sign y se envia un objeto JSON con dos campos
 * envia : {id:[INT],password:[STRING]}
 * recibe: {id:[INT],token:[STRING]}
 * 
 * la priumera vez que un aparatito se conecta se le da un id y contraseña que usa
 * en cada sesion para recivir un token, ese token hay que enviarlo en el header de
 * todas las siguientes peticiones dentor de la variable "authorization" para que el 
 * servidor no te revote
 *
 * peticion GET a /api/devices/config/{id del dispositivo} obtiene un objeto JSON con 5 campos
 * esto te devuelve TU configuracion
 * envia: [
 * espid    :[INT]
 * field    :[STRING]   //nombre del campo a configurar
 * groupid  :[INT]
 * id       :[INT]      //vale mierda, es cosa del orden
 * value    :[STRING]   //el valor del campo configurado
 * },...]
 *
 * peticion POST a /api/devices/config obtiene un objeto JSON con 5 campos
 * el esp envia las configuraciones que tiene disponibles para modificar
 * se deberia usar solo la primera primera vez que se conecta al servidor
 * envia: [{
 * espid    :[INT]
 * field    :[STRING]   //nombre del campo a configurar
 * groupid  :[INT]
 * value    :[STRING]   //el valor del campo configurado
 * },...]
 *
 * peticion POST a /api/devices/data obtiene un objeto JSON con 5 campos
 * envia: [{
 * espid    :[INT]      //id del dispositivo
 * type     :[STRING]
 * value    :[STRING]
 * timestamp:[DataIso]
 * 
 * },...]
 */

#define TAG "main"

#define DEFAULT_SSID "MAL-config-net"
#define DEFAULT_PASSWORD "configuration"
#define DEFAULT_SSID "quesito"
#define DEFAULT_PASSWORD "quesosod"
#define DHT_PIN 14

int returns;
nvs_handle_t eeprom;

esp_err_t wE(nvs_handle_t handle, const char* key, const int value){
    esp_err_t err=nvs_set_i32(handle, key, value);
    if (err!=ESP_OK)ESP_LOGE("NVS", "Error while seving int: %s", esp_err_to_name(err));
    else nvs_commit(handle);
    return err;
}
esp_err_t wE(nvs_handle_t handle, const char* key, const double value){
    esp_err_t err=nvs_set_blob(handle, key, &value, sizeof(value));
    if (err!=ESP_OK)ESP_LOGE("NVS", "Error while seving double: %s", esp_err_to_name(err));
    else nvs_commit(handle);
    return err;
}
esp_err_t wE(nvs_handle_t handle, const char* key, const bool value){
    esp_err_t err=nvs_set_u8(handle, key, value);
    if (err!=ESP_OK)ESP_LOGE("NVS", "Error while seving boolean: %s", esp_err_to_name(err));
    else nvs_commit(handle);
    return err;
}
esp_err_t wE(nvs_handle_t handle, const char* key, const char* value){
    esp_err_t err=nvs_set_str(handle, key, value);
    if (err!=ESP_OK)ESP_LOGE("NVS", "Error while seving CString: %s", esp_err_to_name(err));
    else nvs_commit(handle);
    return err;
}
esp_err_t wE(nvs_handle_t handle, const char* key, const std::string &value){
    esp_err_t err=nvs_set_str(handle, key, value.c_str());
    if (err!=ESP_OK)ESP_LOGE("NVS", "Error while seving string: %s", esp_err_to_name(err));
    else nvs_commit(handle);
    return err;
}

extern "C" void app_main() {
    //analog pins resolution
    adc1_config_width(ADC_WIDTH_BIT_12);

    //""EEPROM"" initialization
    returns=nvs_flash_init();
    while(returns==ESP_ERR_NVS_NO_FREE_PAGES || returns==ESP_ERR_NVS_NEW_VERSION_FOUND){
        ESP_LOGE(TAG,"Error while initializing the \"EEPROM\"");
        ESP_ERROR_CHECK(nvs_flash_erase());
        returns=nvs_flash_init();
    }
    ESP_LOGI(TAG,"\"EEPROM\" initialized succesfully");
    returns=nvs_open("storage", NVS_READWRITE, &eeprom);
    if (returns!=ESP_OK)ESP_LOGE(TAG,"Error while initializing the \"EEPROM\" part 2");

    //DHT22 init
    DHT22 humedad(DHT_PIN);
    ESP_LOGI(TAG,"DHT22 initialized");

    wifi::init();
    wifi::connect(DEFAULT_SSID,DEFAULT_PASSWORD);
    HttpClient peticiones("https://quesito.requestcatcher.com/test");
    peticiones.set_method(Method::POST);
    std::string respuesta, body;
    while (1){
        int8_t status = humedad.readSensorData();
        if(status!=0)
            ESP_LOGW(TAG,"humidity sensor error. code:%d",status);

        ESP_LOGI(TAG, "Humedad: %.1f %% | Temperatura: %.1f °C | PPM: %d ",
                humedad.getHumidity(), humedad.getTemperature(),getAnalog(1));
        body=std::to_string(humedad.getTemperature());
        peticiones.set_body(body);
        peticiones.perform(respuesta);
        delayMS(3000);
    }
}
