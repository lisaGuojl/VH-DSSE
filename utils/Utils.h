#ifndef UTILS_H
#define UTILS_H

#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <openssl/md5.h>


//#define AES_BLOCK_SIZE 16
#define DIGEST_SIZE 16
#define GGM_SIZE 4294967296 //2^32



int aes_encrypt(unsigned char* plaintext, int plaintext_len,
    unsigned char* key, unsigned char* iv,
    unsigned char* ciphertext);

int aes_decrypt(unsigned char* ciphertext, int ciphertext_len,
    unsigned char* key, unsigned char* iv,
    unsigned char* plaintext);

void sha256_digest(unsigned char* plaintext, int plaintext_len,
    unsigned char* digest);

void md5_digest(unsigned char* plaintext, int plaintext_len,
    unsigned char* digest);

unsigned int key_derivation(unsigned char* plaintext, int plaintext_len,
    unsigned char* key, int key_len,
    unsigned char* digest);


#endif
