#include "cJSON.h"
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
 *
 *
 *
 *
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

/*
 * ---EEPROM KEYS---
 *  "link"
 *  "ssid"
 *  "ssidp"
 *
 * */

#define TAG "main"

#define DEFAULT_SSID "MAL-config-net"
#define DEFAULT_PASSWORD "configuration"
#define DHT_PIN 14

bool doRequest=false;
nvs_handle_t eeprom;
int returns;
cJSON *parser;
std::string password,myData;
int32_t id;


//TODO: mover esto a un componente aparte
//write
esp_err_t wE(nvs_handle_t handle, const char* key, const int32_t value){
    esp_err_t err=nvs_set_i32(handle, key, value);
    if(err==ESP_OK)return nvs_commit(handle);
    ESP_LOGE("NVS", "Error while seving int: %s", esp_err_to_name(err));
    return err;
}
esp_err_t wE(nvs_handle_t handle, const char* key, const double value){
    esp_err_t err=nvs_set_blob(handle, key, &value, sizeof(value));
    if(err==ESP_OK)return nvs_commit(handle);
    ESP_LOGE("NVS", "Error while seving double: %s", esp_err_to_name(err));
    return err;
}
esp_err_t wE(nvs_handle_t handle, const char* key, const bool value){
    esp_err_t err=nvs_set_u8(handle, key, value);
    if(err==ESP_OK)return nvs_commit(handle);
    ESP_LOGE("NVS", "Error while seving boolean: %s", esp_err_to_name(err));
    return err;
}
esp_err_t wE(nvs_handle_t handle, const char* key, const char* value){
    esp_err_t err=nvs_set_str(handle, key, value);
    if(err==ESP_OK)return nvs_commit(handle);
    ESP_LOGE("NVS", "Error while seving CString: %s", esp_err_to_name(err));
    return err;
}
esp_err_t wE(nvs_handle_t handle, const char* key, const std::string &value){
    esp_err_t err=nvs_set_str(handle, key, value.c_str());
    if(err==ESP_OK)return nvs_commit(handle);
    ESP_LOGE("NVS", "Error while seving string: %s", esp_err_to_name(err));
    return err;
}

//read
esp_err_t rE(nvs_handle_t handle, const char* key, int32_t &out_value){
    esp_err_t err=nvs_get_i32(handle, key, &out_value);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGW("NVS", "Int key not found: %s", key);
    } else if (err != ESP_OK) {
        ESP_LOGE("NVS", "Error reading int: %s", esp_err_to_name(err));
    }
    return err;
}
esp_err_t rE(nvs_handle_t handle, const char* key, double &out_value){
    size_t size=sizeof(double);
    esp_err_t err=nvs_get_blob(handle, key, &out_value, &size);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGW("NVS", "Double key not found: %s", key);
    } else if (err != ESP_OK) {
        ESP_LOGE("NVS", "Error reading double: %s", esp_err_to_name(err));
    }
    return err;
}
esp_err_t rE(nvs_handle_t handle, const char* key, bool &out_value){
    uint8_t v=0;
    esp_err_t err=nvs_get_u8(handle, key, &v);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGW("NVS", "Bool key not found: %s", key);
    } else if (err != ESP_OK) {
        ESP_LOGE("NVS", "Error reading bool: %s", esp_err_to_name(err));
    }
    out_value=(v != 0);
    return err;
}
esp_err_t rE(nvs_handle_t handle, const char* key, std::string &out_value){
    size_t required_size;
    esp_err_t err=nvs_get_str(handle, key, NULL, &required_size);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGW("NVS", "String key not found: %s", key);
        return err;
    }
    if (err != ESP_OK) return err;

    char *buffer=(char*)malloc(required_size);
    if (!buffer) return ESP_ERR_NO_MEM;

    err=nvs_get_str(handle, key, buffer, &required_size);
    if (err == ESP_OK) out_value=buffer;
    else ESP_LOGE("NVS", "Error reading string: %s", esp_err_to_name(err));

    free(buffer);
    return err;
}

cJSON* objeter(const char* type, const char* value, const char* timestamp="2025-08-18T20:15:30Z"){
    cJSON *objt=cJSON_CreateObject();
    cJSON_AddNumberToObject(objt, "espid", id);
    cJSON_AddStringToObject(objt, "type", type);
    cJSON_AddStringToObject(objt, "value", value);
    cJSON_AddStringToObject(objt, "timestamp", timestamp);
    return objt;
}

extern "C" void app_main() {
    //TODO: comandos AT falsos para cargar el link en el nvs
    //char line[MAX_CMD_LEN];
    //while (1) {
    //    if (fgets(line, sizeof(line), stdin) != NULL) {
    //        line[strcspn(line, "\r\n")] = 0; // quitar \n
    //        process_command(line);
    //    }

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
    if(returns!=ESP_OK)ESP_LOGE(TAG,"Error while initializing the \"EEPROM\" part 2");

    //DHT22 init
    DHT22 humedad(DHT_PIN);
    ESP_LOGI(TAG,"DHT22 initialized");

    //WIFI set-up
    wifi::init();

    std::string ssid=DEFAULT_SSID,ssidp=DEFAULT_PASSWORD;
    returns=rE(eeprom, "ssid", ssid);
    if(returns==ESP_ERR_NVS_NOT_FOUND){
        ESP_LOGI(TAG,"conecting to default wifi network");
    }else{
        ESP_LOGI(TAG,"conecting to private wifi network");
        returns=rE(eeprom, "ssidp", ssidp);
    };
    returns=wifi::connect(ssid.c_str(),ssidp.c_str());

    //HTTP init
    std::string link,respuesta, body;
    returns=rE(eeprom,"link",link);
    while(returns==ESP_ERR_NVS_NOT_FOUND){
        ESP_LOGE(TAG,"no url saved in nvs");
        delayMS(5000);
    }
    HttpClient peticiones(link);
    peticiones.set_method(Method::POST);

    //board identification info
    returns=rE(eeprom,"id",id);
    if(returns==ESP_ERR_NVS_NOT_FOUND&&wifi::isConnected()){
        peticiones.perform("/api/devices/sign", respuesta);
        parser=cJSON_Parse(respuesta.c_str());
        if(!parser){
            ESP_LOGE("JSON", "login server not responding or giving useless information. server responce: %s. rebooting...", respuesta.c_str());
            esp_restart();
        }
        id=cJSON_GetObjectItem(parser,"id")->valueint;
        password=cJSON_GetObjectItem(parser,"password")->valuestring;
        returns=wE(eeprom,"id",id);
        returns=wE(eeprom,"password",password);
        myData=cJSON_PrintUnformatted(parser);
        cJSON_Delete(parser);
    }else returns=rE(eeprom,"password",password);
    if(myData.empty()){
        parser=cJSON_CreateObject();
        cJSON_AddNumberToObject(parser, "id", id);
        cJSON_AddStringToObject(parser, "password", password.c_str());
        myData=cJSON_PrintUnformatted(parser);
        cJSON_Delete(parser);
    }
    peticiones.set_body(myData);
    peticiones.set_method(Method::PUT);
    peticiones.perform("/api/devices/sign", respuesta);
    parser=cJSON_Parse(respuesta.c_str());


    //main loop
    peticiones.set_method(Method::POST);
    cJSON *petition=cJSON_CreateArray();
    while (1){
        returns=humedad.readSensorData();
        if(returns!=0)
            ESP_LOGW(TAG,"humidity sensor error. code:%d",returns);

        ESP_LOGI(TAG, "Humedad: %.1f %% | Temperatura: %.1f °C | PPM: %d ",
                humedad.getHumidity(), humedad.getTemperature(),getAnalog(1));

        cJSON_AddItemToArray(petition,objeter("temperature",
                    std::to_string(humedad.getTemperature()).c_str()));
        cJSON_AddItemToArray(petition,objeter("humedad",
                    std::to_string(humedad.getHumidity()).c_str()));
        cJSON_AddItemToArray(petition,objeter("PPM",
                    std::to_string(getAnalog(1)).c_str()));
        //JSON_AddItemToArray(petition,objeter("",std::to_string()));
        if(!wifi::isConnected()){
            peticiones.set_body(cJSON_PrintUnformatted(petition));
            peticiones.perform("/api/devices/data", respuesta);
            cJSON_Delete(petition);
            cJSON *petition=cJSON_CreateArray();
        }
        body=std::to_string(humedad.getTemperature());
        peticiones.set_body(body);
        peticiones.perform(respuesta);
        delayMS(3000);
    }
}









































