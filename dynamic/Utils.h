#ifndef PUNCTURABLE_PRF_UTILS_H
#define PUNCTURABLE_PRF_UTILS_H

#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <openssl/md5.h>

//#include <sstream>
//#include <iomanip>

#define AES_BLOCK_SIZE 16
#define DIGEST_SIZE 32
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


unsigned int hmac_digest(unsigned char* plaintext, int plaintext_len,
    unsigned char* key, int key_len,
    unsigned char* digest);

//std::string uint82hex(const uint8_t* data, int data_length) {
//    std::stringstream ss;
//    ss << std::hex << std::setfill('0');
//    for (int i = 0; i < data_length; ++i)
//        ss << std::setw(2) << static_cast<unsigned>(data[i]);
//    std::string mystr = ss.str();
//    return mystr;
//}

#endif
