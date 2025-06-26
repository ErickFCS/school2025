// http.cpp
#include "http.hpp"
#include "esp_log.h"
#include <vector>

static const char* TAG = "HttpClient";

HttpClient::HttpClient(const std::string& url){
    config_ = {};
    config_.url = url.c_str();
    config_.timeout_ms = 5000;
    client_ = esp_http_client_init(&config_);
    if (!client_){
        ESP_LOGE(TAG, "Error init http client");
        //TODO: AGREGAR MANEJO DE ERRORES ACA
    }
    esp_http_client_set_method(client_, HTTP_METHOD_GET);
}

HttpClient::~HttpClient(){
    if (client_)esp_http_client_cleanup(client_);
}

void HttpClient::set_method(Method method){
    esp_http_client_set_method(client_, to_esp_method(method));
}

void HttpClient::set_header(const std::string& key, const std::string& value){
    headers_[key] = value;
}

void HttpClient::set_body(const std::string& body){
    body_ = body;
}

int HttpClient::perform(std::string& out_response){
    // Aplica cabeceras
    for (auto& kv : headers_){
        esp_err_t err = esp_http_client_set_header(client_, kv.first.c_str(), kv.second.c_str());
        if (err != ESP_OK){
            ESP_LOGE(TAG, "Error setting header %s", kv.first.c_str());
            return -1;
        }
    }

    // Aplica cuerpo si hay
    if (!body_.empty())
        esp_http_client_set_post_field(client_, body_.c_str(), body_.length());

    // Ejecuta
    esp_err_t err = esp_http_client_perform(client_);
    if (err != ESP_OK){
        ESP_LOGE(TAG, "HTTP request failed: %s", esp_err_to_name(err));
        return -1;
    }

    // Codigo de respuesta
    int status = esp_http_client_get_status_code(client_);
    int len = esp_http_client_fetch_headers(client_);
    // Lee el body en buffer
    int content_length = esp_http_client_get_content_length(client_);
    std::vector<char> buffer(content_length + 1);
    int read_len = esp_http_client_read_response(client_, buffer.data(), content_length);
    if (read_len >= 0){
        buffer[read_len] = '\0';
        out_response.assign(buffer.data(), read_len);
    } else {
        ESP_LOGW(TAG, "No response body or error reading it");
        out_response.clear();
    }

    return status;
}

esp_http_client_method_t HttpClient::to_esp_method(Method m){
    switch (m){
        case Method::GET:    return HTTP_METHOD_GET;
        case Method::POST:   return HTTP_METHOD_POST;
        case Method::PUT:    return HTTP_METHOD_PUT;
        case Method::DELETE: return HTTP_METHOD_DELETE;
    }
    return HTTP_METHOD_GET;
}
