#include <stdio.h>
#include "esp-rcnow.h"

static const char *TAG = "esp-rcnow-tx";

void app_main(void)
{

    // Initialize NVS and ESP-NOW
    esp_rcnow_start();

}
