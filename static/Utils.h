#ifndef PUNCTURABLE_PRF_UTILS_H
#define PUNCTURABLE_PRF_UTILS_H

#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
//#include <QByteArray>

#define AES_BLOCK_SIZE 16
#define DIGEST_SIZE 32
#define GGM_SIZE 4294967296 //2^3
#define HASH_SIZE 3
#define L 128

int aes_encrypt(unsigned char* plaintext, int plaintext_len,
    unsigned char* key, unsigned char* iv,
    unsigned char* ciphertext);

int aes_decrypt(unsigned char* ciphertext, int ciphertext_len,
    unsigned char* key, unsigned char* iv,
    unsigned char* plaintext);


unsigned int hmac_digest(unsigned char* plaintext, int plaintext_len,
    unsigned char* key, int key_len,
    unsigned char* digest);

void sha256_digest(unsigned char *plaintext, int plaintext_len,
                unsigned char *digest);
#endif
