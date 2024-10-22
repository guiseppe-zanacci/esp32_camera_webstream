#ifndef FCT_H
#define FCT_H

#include "esp_camera.h"
#include <WiFi.h>
#include <ArduinoWebsockets.h>
#include "esp_timer.h"
#include "img_converters.h"
#include "fb_gfx.h"
#include "soc/soc.h" //disable brownout problems
#include "soc/rtc_cntl_reg.h" //disable brownout problems
#include "driver/gpio.h"

extern esp_err_t init_camera();
extern esp_err_t init_wifi();

using namespace websockets;
extern WebsocketsClient client;

#endif