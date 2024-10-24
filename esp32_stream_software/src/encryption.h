#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string.h>
#include <esp_camera.h>

void aes_encrypt_cleartext_message(const unsigned char* cleartext_message, size_t cleartext_message_len, unsigned char* encrypted_cleartext_message, const unsigned char* key, const unsigned char* iv);
unsigned char* encrypt_frame_buffer(const unsigned char* frame_data, size_t frame_buffer_length, const unsigned char* key, const unsigned char* iv);
const unsigned char* convertCharToUnsignedChar(const char* input);


#endif
