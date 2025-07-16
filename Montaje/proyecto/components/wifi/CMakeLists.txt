idf_component_register(SRCS "wifi.cpp"
                    REQUIRES nvs_flash esp_event esp_wifi
                    INCLUDE_DIRS ".")
