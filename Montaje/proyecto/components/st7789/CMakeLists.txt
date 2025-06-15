set(srcs "st7789.cpp" "st7789or.c" "fontx.c" "decode_png.c" "decode_jpeg_v5.c" "pngle.c")

idf_component_register(SRCS "${srcs}"
                       PRIV_REQUIRES driver spiffs esp_rom esp_jpeg
                       INCLUDE_DIRS ".")
