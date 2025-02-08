#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include "esp-now-txrx.h"

static const char *TAG = "esp-rcnow";


esp_err_t esp_rcnow_start(void)
{

    esp_err_t err = ESP_FAIL;
    err = esp_rcnow_init();

    return err;
}
