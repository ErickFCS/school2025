idf_component_register(SRCS "pinControl.cpp"
                        REQUIRES "esp_driver_gpio"
                        REQUIRES driver
                        INCLUDE_DIRS ".")
