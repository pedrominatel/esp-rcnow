#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
#include "esp_system.h"
#include "esp_wifi.h"

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 4, 0)
#include "esp_mac.h"
#endif

//ESP-NOW
#include "espnow.h"
#include "espnow_storage.h"
#include "espnow_utils.h"

#include "esp-rcnow.h"

static const char *TAG = "esp-rcnow";

// Function to bind the receiver to the transmitter
static void espnow_bind_receiver(const uint8_t *mac_addr)
{
    esp_now_peer_info_t peer_info;
    memset(&peer_info, 0, sizeof(esp_now_peer_info_t));
    peer_info.channel = CONFIG_ESPNOW_CHANNEL;
    peer_info.ifidx = ESP_IF_WIFI_STA;
    peer_info.encrypt = false;
    memcpy(peer_info.peer_addr, mac_addr, ESP_NOW_ETH_ALEN);
    ESP_ERROR_CHECK(esp_now_add_peer(&peer_info));
}

static void app_wifi_init()
{
    esp_event_loop_create_default();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_ps(WIFI_PS_NONE));
    ESP_ERROR_CHECK(esp_wifi_start());
    
}

esp_err_t esp_rcnow_init(void)
{
    espnow_storage_init();
    app_wifi_init();

    espnow_config_t espnow_config = ESPNOW_INIT_CONFIG_DEFAULT();
    espnow_init(&espnow_config);

    ESP_LOGI(TAG, "ESP-NOW initialization complete");
    return ESP_OK;
}

esp_err_t esp_rcnow_denit(void)
{
    return ESP_OK;
}
