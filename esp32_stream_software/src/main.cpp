#include "credentials.h"
#include "fct.h"
#include "encryption.h"

const unsigned char* aes_key;
const unsigned char* aes_iv;

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brown out

  Serial.begin(9600);
  Serial.setDebugOutput(true);

  Serial.println("Started");

  init_camera();
  init_wifi();

  const unsigned char* aes_key = convertCharToUnsignedChar(aes_key_hex);
  const unsigned char* aes_iv = convertCharToUnsignedChar(aes_iv_hex);
}

void loop() {
  if (client.available()) {
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) { // if (no_image) {nuke__entire_system;}
      Serial.println("img capture failed");
      esp_camera_fb_return(fb);
      ESP.restart();
    }
    unsigned char* message_to_send = encrypt_frame_buffer((const unsigned char*) fb->buf, fb->len, aes_key, aes_iv);
    client.sendBinary((const char*) fb->buf, fb->len);
    Serial.println("image sent");
    esp_camera_fb_return(fb);
    client.poll();
  }
}
