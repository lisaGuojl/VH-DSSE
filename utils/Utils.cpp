#include "Utils.h"
#if OPENSSL_VERSION_NUMBER >= 0x10100000L
int aes_encrypt(unsigned char* plaintext, int plaintext_len,
    unsigned char* key, unsigned char* iv,
    unsigned char* ciphertext) {
    EVP_CIPHER_CTX* ctx;

    int len = 0;

    int ciphertext_len;

    /* Create and initialise the context */
    ctx = EVP_CIPHER_CTX_new();

    /* Initialise the encryption operation. */
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);

    /* Encrypt the message */
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len);
    ciphertext_len = len;

    /* Finalise the encryption */
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int aes_decrypt(unsigned char* ciphertext, int ciphertext_len,
    unsigned char* key, unsigned char* iv,
    unsigned char* plaintext) {
    EVP_CIPHER_CTX* ctx;

    int len = 0;

    int plaintext_len;

    /* Create and initialise the context */
    ctx = EVP_CIPHER_CTX_new();

    /* Initialise the decryption operation. */
    EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);

    /* decrypt the message */
    EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len);
    plaintext_len = len;

    /* Finalise the encryption */
    EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}

#else
int aes_encrypt(unsigned char* plaintext, int plaintext_len,
    unsigned char* key, unsigned char* iv,
    unsigned char* ciphertext) {
    EVP_CIPHER_CTX ctx;

    int len = 0;

    int ciphertext_len;

    /* Create and initialise the context */
    EVP_CIPHER_CTX_init(&ctx);

    /* Initialise the encryption operation. */
    EVP_EncryptInit_ex(&ctx, EVP_aes_128_cbc(), NULL, key, iv);

    /* Encrypt the message */
    EVP_EncryptUpdate(&ctx, ciphertext, &len, plaintext, plaintext_len);
    ciphertext_len = len;

    /* Finalise the encryption */
    EVP_EncryptFinal_ex(&ctx, ciphertext + len, &len);
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_cleanup(&ctx);

    return ciphertext_len;
}

int aes_decrypt(unsigned char* ciphertext, int ciphertext_len,
    unsigned char* key, unsigned char* iv,
    unsigned char* plaintext) {
    EVP_CIPHER_CTX ctx;

    int len = 0;

    int plaintext_len;

    /* Create and initialise the context */
    EVP_CIPHER_CTX_init(&ctx);

    /* Initialise the decryption operation. */
    EVP_DecryptInit_ex(&ctx, EVP_aes_128_cbc(), NULL, key, iv);

    /* decrypt the message */
    EVP_DecryptUpdate(&ctx, plaintext, &len, ciphertext, ciphertext_len);
    plaintext_len = len;

    /* Finalise the encryption */
    EVP_DecryptFinal_ex(&ctx, plaintext + len, &len);
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_cleanup(&ctx);

    return plaintext_len;
}

#endif

void sha256_digest(unsigned char* plaintext, int plaintext_len,
    unsigned char* digest) {
    /* Create and initialise the context */
    SHA256_CTX ctx;
    SHA256_Init(&ctx);

    /* compute the digest */
    SHA256_Update(&ctx, plaintext, plaintext_len);

    /* Finalise the digest */
    SHA256_Final(digest, &ctx);
}

void md5_digest(unsigned char* plaintext, int plaintext_len,
    unsigned char* digest) {
    /* Create and initialise the context */
    MD5_CTX ctx;
    MD5_Init(&ctx);

    /* compute the digest */
    MD5_Update(&ctx, plaintext, plaintext_len);

    /* Finalise the digest */
    MD5_Final(digest, &ctx);
}
