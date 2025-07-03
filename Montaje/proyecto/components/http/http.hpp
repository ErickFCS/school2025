// http.hpp
#pragma once

#include "esp_http_client.h"
#include <string>
#include <map>

class HttpClient {
public:
    enum class Method { GET, POST, PUT, DELETE };

    HttpClient(const std::string& url);
    ~HttpClient();

    // Configuracion
    void set_method(Method method);
    void set_header(const std::string& key, const std::string& value);
    void set_body(const std::string& body);

    // Ejecuta la peticion y devuelve respuesta en formato string
    // Lanza excepcion o retorna código de error < 0 si falla
    int perform(std::string& out_response);

private:
    esp_http_client_handle_t client_;
    esp_http_client_config_t config_;

    std::map<std::string, std::string> headers_;
    std::string body_;

    // Convierte Method a constante ESP-IDF
    static esp_http_client_method_t to_esp_method(Method m);
};;
