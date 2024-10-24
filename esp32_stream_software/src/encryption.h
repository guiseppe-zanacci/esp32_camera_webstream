#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string.h>

void aes_encrypt_cleartext_message(const unsigned char* cleartext_message, size_t cleartext_message_len, unsigned char* encrypted_cleartext_message, const unsigned char* key, const unsigned char* iv);

#endif
