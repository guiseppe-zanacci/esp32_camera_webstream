#include "mbedtls/aes.h"
#include <string.h>
#include <stdio.h>
#include "esp_camera.h"

// Function to convert const char* to const unsigned char*
const unsigned char* convertCharToUnsignedChar(const char* input) {
    size_t len = strlen(input);  // Get the length of the input string
    unsigned char* output = (unsigned char*)malloc(len + 1);  // Allocate memory for unsigned char array (+1 for null terminator)

    // Copy each char into the unsigned char array
    for (size_t i = 0; i < len; i++) {
        output[i] = (unsigned char)input[i];
    }

    output[len] = '\0';  // Null-terminate the new string
    return output;       // Return as const unsigned char*
}

void aes_encrypt_cleartext_message(const unsigned char* cleartext_message, size_t cleartext_message_len, unsigned char* encrypted_cleartext_message, const unsigned char* key, const unsigned char* iv) {
    
    mbedtls_aes_context aes;
    unsigned char iv_copy[16]; // CBC mode needs an IV per block, we use a copy of the original IV

    // Initialize the AES context and set the key for encryption
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_enc(&aes, key, 128);  // 128-bit AES key
    
    // Copy the IV because it will be modified during encryption
    memcpy(iv_copy, iv, 16);

    // Calculate the number of blocks to process (cleartext_message_len rounded up to nearest 16)
    size_t block_count = (cleartext_message_len + 15) / 16;  // Round up to the next block
    size_t last_block_size = cleartext_message_len % 16;     // The size of the last partial block, if any

    // Encrypt each 16-byte block
    for (size_t i = 0; i < block_count; i++) {
        unsigned char block[16] = {0}; // Prepare a block of 16 bytes

        if (i == block_count - 1 && last_block_size > 0) {
            // Last block, add PKCS#7 padding if needed
            memcpy(block, cleartext_message + i * 16, last_block_size);  // Copy the remaining data
            unsigned char padding = 16 - last_block_size;    // PKCS#7 padding value
            for (size_t j = last_block_size; j < 16; j++) {
                block[j] = padding;  // Apply padding
            }
        } else {
            // Normal block (exactly 16 bytes)
            memcpy(block, cleartext_message + i * 16, 16);  // Copy 16 bytes into block
        }

        // Encrypt the block
        mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, 16, iv_copy, block, encrypted_cleartext_message + i * 16);
    }

    mbedtls_aes_free(&aes);  // Free the AES context when done
}


unsigned char* encrypt_frame_buffer(const unsigned char* frame_data, size_t frame_buffer_length, const unsigned char* key, const unsigned char* iv) {

    // Allocate a new buffer for the encrypted data
    size_t padded_length = ((frame_buffer_length + 15) / 16) * 16;  // Round up to next multiple of 16
    //unsigned char* encrypted_frame_buffer[padded_length]; // Buffer to hold the encrypted message

    // Allocate a separate buffer to copy frame data for encryption
    unsigned char* data_to_encrypt = (unsigned char*)malloc(frame_buffer_length);

        // Allocate memory for the encrypted data buffer
    unsigned char* encrypted_frame_buffer = (unsigned char*)malloc(padded_length);

    // Copy frame data to the new buffer
    memcpy(data_to_encrypt, frame_data, frame_buffer_length);

    // Call the AES encryption function
    aes_encrypt_cleartext_message(data_to_encrypt, frame_buffer_length, encrypted_frame_buffer, key, iv);

    // Free the allocated memory
    free(data_to_encrypt);

    return encrypted_frame_buffer;
}
