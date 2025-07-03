extern"C"{
    #include "esp_http_client.h"
    #include "esp_log.h"
}
#define MAX_HTTP_OUTPUT_BUFFER 2048
#define IPADDRESSERVER "PONER LA IP DEL 

class http_client{
    char local_response_buffer[MAX_HTTP_OUTPUT_BUFFER + 1] = {0};
public:
    http_client(const char* url);
    void post();
    void get();
};
