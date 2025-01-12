#include <stdio.h>
#include <string.h>

void win(unsigned char* ciphertext, long dataLen, unsigned char* key, long keyLen, unsigned char* plaintext) {
    unsigned char T[256];
    unsigned char S[256];
    unsigned char temp; // Temporary variable for swapping
    int i = 0, j = 0, t = 0;

    // Step 1: Initialize S and T
    for (i = 0; i < 256; i++) {
        S[i] = i;
        T[i] = key[i % keyLen];
    }

    // Step 2: Perform the key-scheduling algorithm (KSA)
    j = 0;
    for (i = 0; i < 256; i++) {
        j = (j + S[i] + T[i]) % 256;

        // Swap S[i] and S[j]
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }

    // Step 3: Decrypt the ciphertext using the pseudo-random generation algorithm (PRGA)
    i = 0;
    j = 0;
    for (long x = 0; x < dataLen; x++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;

        // Swap S[i] and S[j]
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;

        t = (S[i] + S[j]) % 256;

        // XOR the ciphertext byte with the generated keystream byte
        plaintext[x] = ciphertext[x] ^ S[t];
    }
}

int main() {
    // Flag as an array of bytes
    unsigned char flag[40] = {
        0x09, 0x66, 0x72, 0xB6, 0x2B, 0x25, 0x56, 0xE1, 0x1F, 0x23, 0x88, 0x70, 0xB0, 0x41, 0x8A, 0x78, 0x87, 0x14, 0x10, 0xA9, 0x2A, 0x4A, 0x78, 0xDE, 0xA4, 0x74, 0xAF, 0x10, 0xA6, 0xFE, 0xE8, 0x02, 0xCC, 0xF6, 0x8D, 0x3F, 0x41, 0x47, 0xB2
    };
    
    unsigned char decryptedFlag[40]; // Decrypted flag 
    int maze[256] = {
        0,0,0,1, 1,0,1,0, 0,0,1,1, 1,0,0,0, 0,0,0,1, 1,0,1,0, 0,0,1,1, 1,0,0,0,
        1,0,1,1, 1,1,0,1, 1,1,1,0, 0,0,1,1, 1,0,1,0, 0,1,1,1, 1,1,0,1, 1,0,1,0, 
        0,1,0,0, 0,0,1,0, 0,1,0,1, 1,1,0,0, 0,1,0,1, 1,1,0,1, 1,0,0,0 ,0,1,1,0,
        0,0,1,1, 1,1,0,1, 1,0,1,0, 0,0,1,1, 1,0,0,0, 0,0,1,1, 1,0,0,1, 1,1,0,0,
        0,1,1,0, 0,0,0,1, 1,1,1,1, 1,1,0,0, 0,0,1,0, 0,1,0,1, 1,0,0,1, 1,0,1,0,
        1,1,0,0, 0,0,1,1, 1,1,0,1, 1,0,1,0, 0,1,1,1, 1,0,1,1, 1,0,0,0, 0,1,1,0,
        0,0,1,1, 1,1,0,0, 0,0,1,1, 1,1,1,0, 0,1,1,0, 0,1,1,0, 0,0,1,1, 1,1,1,0,
        0,1,0,0, 0,0,0,1, 1,1,0,0, 0,1,0,1, 1,1,0,0, 0,1,0,1, 1,1,0,0, 0,1,0,0,
    };
    
    int box = 0;

    // Input movement string
    char moves[100];
    printf("Enter the moves (w/s/a/d): ");
    scanf("%s", moves);

    if (strlen(moves) != 39) {
        printf("you're stuck\n");
        return 1; // Exit if the input length is not 39
    }

    // Process each move
    for (int i = 0; i < strlen(moves); i++) {
        char move = moves[i];
        int base = box * 4;
        int valid = 0;

        // Check movement validity
        if (move == 'd' && maze[base + 3] == 1 && (box % 8 != 7)) {
            box++;
            valid = 1;
        } else if (move == 'a' && maze[base + 0] == 1 && (box % 8 != 0)) {
            box--;
            valid = 1;
        } else if (move == 's' && maze[base + 2] == 1 && (box < 56)) {
            box += 8;
            valid = 1;
        } else if (move == 'w' && maze[base + 1] == 1 && (box >= 8)) {
            box -= 8;
            valid = 1;
        }

        // If move is invalid, print dead end and exit
        if (!valid) {
            printf("You've reached a dead end\n");
            return 1;
        }
    }

    // Use the user's movement string as the key for RC4 decryption
    win(flag, strlen(flag), (unsigned char*)moves, strlen(moves), decryptedFlag);

    // Output the decrypted flag
    printf("You're out, here's your flag: ");
    for (int i = 0; i < strlen(flag); i++) {
        printf("%c", decryptedFlag[i]);
    }
    printf("\n");

    return 0;
}
