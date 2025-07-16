#pragma once

#include "esp_err.h"
#include "esp_log.h"

#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_wifi.h"

#include "freertos/FreeRTOS.h"

#include <cstring>

namespace wifi{

static void ip_event_cb(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);

static void wifi_event_cb(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);

esp_err_t init(void);

esp_err_t connect(const char* wifi_ssid, const char* wifi_password);

esp_err_t disconnect(void);

esp_err_t deinit(void);

}
