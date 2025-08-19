// http.cpp
#include "http.hpp"
#include "esp_log.h"
#include <vector>

static const char* TAG="HttpClient";

std::string HttpClient::join_url(const std::string& base, const std::string& suffix) {
    if(suffix.empty()) return base;
    if(suffix.find("://") != std::string::npos) return suffix;
    if(base.empty()) return suffix;             //si se da esta condicion sos la caca
    if(base.back()=='/'&&suffix.front()=='/')
        return base.substr(0, base.size()-1)+suffix;
    else if(base.back() != '/'&& suffix.front() != '/')
        return base + '/' + suffix;
    else return base + suffix;
}

HttpClient::HttpClient(const std::string& url){
    uRl=url;
    config_={};
    config_.url=uRl.c_str();
    config_.timeout_ms=5000;
    config_.cert_pem=NULL,  // Esto desactiva la verificación del certificado
    config_.transport_type=HTTP_TRANSPORT_OVER_SSL;
    config_.skip_cert_common_name_check=true;
    client_=esp_http_client_init(&config_);
    if(!client_)ESP_LOGE(TAG, "Error init http client");
    esp_http_client_set_method(client_, HTTP_METHOD_GET);
}

HttpClient::~HttpClient(){
    if(client_)esp_http_client_cleanup(client_);
}

void HttpClient::set_method(Method method){
    esp_http_client_set_method(client_, to_esp_method(method));
}

void HttpClient::set_header(const std::string& key, const std::string& value){
    headers_[key]=value;
}

void HttpClient::set_body(const std::string& body){
    body_=body;
}

int HttpClient::perform(std::string& out_response){
    // Aplica cabeceras
    for (auto& kv : headers_){
        lErr_m= esp_http_client_set_header(client_, kv.first.c_str(), kv.second.c_str());
        if(lErr_m != ESP_OK){
            ESP_LOGE(TAG, "Error setting header %s", kv.first.c_str());
            return -1;
        }
    }
    if(!body_.empty())
        esp_http_client_set_post_field(client_, body_.c_str(), body_.length());
    lErr_m= esp_http_client_perform(client_);
    if(lErr_m != ESP_OK){
        ESP_LOGE(TAG, "HTTP request failed: %s", esp_err_to_name(lErr_m));
        return -1;
    }
    ESP_LOGI(TAG,"statuscode: %d",esp_http_client_get_status_code(this->client_));
    int status=esp_http_client_get_status_code(client_);
    int len=esp_http_client_fetch_headers(client_);
    int content_length=esp_http_client_get_content_length(client_);
    std::vector<char> buffer(content_length + 1);
    int read_len=esp_http_client_read_response(client_, buffer.data(), content_length);
    if(read_len >= 0){
        buffer[read_len]='\0';
        out_response.assign(buffer.data(), read_len);
    } else {
        ESP_LOGW(TAG, "No response body or error reading it");
        out_response.clear();
    }
    return status;
}
int HttpClient::perform(const std::string& suffix, std::string& out_response){
    if (suffix.empty()) return perform(out_response);
    std::string old_url=uRl;
    uRl=join_url(old_url, suffix); //coherencia interna
    // Actualizar la URL del client
    lErr_m=esp_http_client_set_url(client_, uRl.c_str());
    if (lErr_m != ESP_OK) {
        ESP_LOGE(TAG, "esp_http_client_set_url failed: %d", lErr_m);
        uRl=old_url;
        return -1;
    }
    int status=perform(out_response);
    uRl=old_url;
    lErr_m=esp_http_client_set_url(client_, uRl.c_str());
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
