#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

#define BUFFER_SIZE 68 // Fixed buffer size
#define VERIFY_PREFIX "inctfj{"
#define VERIFY_SUFFIX "}"

void swap_halves(char *buffer, size_t len) {
    size_t half_len = len / 2;
    for (size_t i = 0; i < half_len; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[i + half_len];
        buffer[i + half_len] = temp;
    }
}

void xor_decrypt(char *buffer, size_t len) {
    const unsigned char xor_values[] = {0x2A, 0x39, 0x45, 0x77, 0x59};
    size_t xor_values_count = sizeof(xor_values) / sizeof(xor_values[0]);

    for (size_t i = 0; i < len; i++) {
        buffer[i] ^= xor_values[i % xor_values_count];
    }
}

void reverse_buffer(char *buffer, size_t len) {
    for (size_t i = 0; i < len / 2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[len - i - 1];
        buffer[len - i - 1] = temp;
    }
}

int decrypt_data(char *buffer, size_t len) {
    if (len != BUFFER_SIZE) {
        fprintf(stderr, "Invalid buffer length for decryption\n");
        return 0; // Failure
    }

    // Step 1: Swap halves of the buffer
    swap_halves(buffer, len);

    // Step 2: XOR decrypt based on index
    xor_decrypt(buffer, len);

    // Step 3: Reverse the buffer
    reverse_buffer(buffer, len);

    // Step 4: Check for "inctfj{" and "}" in the decrypted buffer
    if (strstr(buffer, VERIFY_PREFIX) && strchr(buffer, VERIFY_SUFFIX[0])) {
        return 1; // Success
    } else {
        return 0; // Failure
    }
}

int main() {
    const char server_ip[] = {'1', '7', '2', '.', '2', '3', '.', '8', '5', '.', '1', '0', '6', '\x00'};
    const int server_port = 1337;

    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    ssize_t received_bytes;
    const char message[] = {'H', 'e', 'l', 'l', 'o', ' ', 'C', '2', ' ', 's', 'e', 'r', 'v', 'e', 'r', ',', ' ', 'I', 'n', 'C', 'T', 'F', 'j', ' ', 'p', 'a', 'r', 't', 'i', 'c', 'i', 'p', 'a', 'n', 't', ' ', 'h', 'e', 'r', 'e', '\n', '\x00'};

    // Create the socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        // perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        // perror("Invalid address/ Address not supported");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        // perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // printf("Connected to %s:%d\n", server_ip, server_port);

    // Send message to the server
    if (send(sock, message, strlen(message), 0) < 0) {
        // perror("Sending message failed");
        close(sock);
        exit(EXIT_FAILURE);
    }
    // printf("Message sent: %s\n", message);

    // Receive data from the server
    received_bytes = recv(sock, buffer, BUFFER_SIZE, 0);
    if (received_bytes < 0) {
        // perror("Receiving failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    if (received_bytes != BUFFER_SIZE) {
        // fprintf(stderr, "Unexpected buffer size received: %zd\n", received_bytes);
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Decrypt and verify the data
    if (decrypt_data(buffer, BUFFER_SIZE)) {
        printf("Decryption successful! Valid data received.\n");
    } else {
        fprintf(stderr, "Decryption failed. Invalid data received.\n");
    }

    // Close the socket
    close(sock);

    return 0;
}
