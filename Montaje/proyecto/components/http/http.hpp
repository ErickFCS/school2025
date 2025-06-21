extern"C"{
    #include "esp_http_client.h"
    #include "esp_log.h"
    #include <sys/param.h>
    #include <string.h>
    #include <sys/param.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include "esp_log.h"
    #include "nvs_flash.h"
    #include "esp_event.h"
    #include "esp_netif.h"
    #include "esp_tls.h"
#if CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
    #include "esp_crt_bundle.h"
#endif
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "esp_system.h"
}
#define MAX_HTTP_OUTPUT_BUFFER 2048
static const char *TAG = "HTTP_CLIENT";

esp_err_t _http_event_handler(esp_http_client_event_t *evt);

class http_client{
    char local_response_buffer[MAX_HTTP_OUTPUT_BUFFER + 1] = {0};
public:
    http_client(const char* url);
    void post();
    void get();
};
