idf_component_register(SRCS "http.cpp"
                    PRIV_REQUIRES esp_http_client nvs_flash esp_netif esp-tls
                    INCLUDE_DIRS ".")
