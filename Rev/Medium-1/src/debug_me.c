#include <sys/ptrace.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

// AES key and IV
static unsigned char key[16] = {
    0x01, 0x12, 0x23, 0x33, 0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
};

static const unsigned char iv[16] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 11, 22, 33, 44, 55
};

// Encrypted flag
static const unsigned char ciphertext[] = {
   0x83,
    0x5a,
    0x88,
    0xa9,
    0x08,
    0x36,
    0xbf,
    0xaf,
    0x7d,
    0xb6,
    0x3d,
    0x00,
    0xd2,
    0xd3,
    0x84,
    0x66,
    0x8a,
    0x6d,
    0x85,
    0x02,
    0x87,
    0xf7,
    0x15,
    0xe6,
    0xb8,
    0x33,
    0x9d,
    0x21,
    0xcd,
    0xf7,
    0x87,
    0x0a
};

void handleErrors() {
    fprintf(stderr, "An error occurred\n");
    exit(1);
}

// AES decryption function
int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *plaintext, int value) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len;


    if (!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    if (EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv) != 1)
        handleErrors();

    if (EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len) != 1)
        handleErrors();
    plaintext_len = len;

    if (EVP_DecryptFinal_ex(ctx, plaintext + len, &len) != 1)
        handleErrors();
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    return plaintext_len;
}

void anti_debug_ptrace() {
    if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1) {
        printf("Debugger detected. Exiting!\n");
        exit(0);
    }
}

int sussy_debug() {
    return (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1);
}

void decrypt_flag(int val) {
    if (val == 208) {
        for(int i = 0; i< 3; i++)
        {
            key[i] = key[i] -1;
        }
    }
    else if (val == 176)
    {
        for(int i = 0; i< 3; i++)
        {
            key[i] = key[i] + 1;
        }
    }
    unsigned char decryptedtext[128];
    int decryptedtext_len;

    decryptedtext_len = decrypt((unsigned char *)ciphertext, sizeof(ciphertext),
                                (unsigned char *)key, (unsigned char *)iv, decryptedtext, val);


    decryptedtext[decryptedtext_len] = '\0';
    
}

int main() {
    anti_debug_ptrace();
    printf("Debugging check in progress...\n");

    int val = sussy_debug() ? 208 : 176;

    printf("Decrypting the flag...\n");
    decrypt_flag(val);

    printf("Flag has been generated.\nBye!\n");
    return 0;
}
