#include <stdio.h>
#include <string.h>
#include "../include/vsh.h"
#include "sha256/sha256.h"

#define SHA256_HEX_SIZE (SHA256_BLOCK_SIZE * 2 + 1) // 64 hex chars + null
#define MAX_BUFFER 1024 // Max buffer size for input and temp strings

// Calculate number of iterations needed for desired bit size
static int calculateIterations(int size) {
    return (size + 255) / 256; // Ceiling division
}

// Generate a new seed using SHA-256 for cryptographic security
static unsigned int generateSeed(const char *input, int len, unsigned int prev_seed) {
    SHA256_CTX ctx;
    BYTE hash[SHA256_BLOCK_SIZE];
    char seed_input[MAX_BUFFER];

    // Combine input and previous seed
    snprintf(seed_input, MAX_BUFFER, "%s%u", input, prev_seed);
    
    sha256_init(&ctx);
    sha256_update(&ctx, seed_input, strlen(seed_input));
    sha256_final(&ctx, hash);

    // Use first 4 bytes as new seed
    return *(unsigned int*)hash;
}

// Convert binary hash to hexadecimal string
static void hashToHex(const BYTE *hash, char *hex) {
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
        sprintf(hex + (i * 2), "%02x", hash[i]);
    }
    hex[SHA256_HEX_SIZE - 1] = '\0';
}

// Select 16 hex characters from the hash using seed
static unsigned int select16HexChars(char *input, char *dest, const char *src, unsigned int seed) {
    int i = 0;
    char temp[17]; // Buffer for 16 hex chars + null

    while (i < 16) {
        seed = generateSeed(input, strlen(input), seed);
        int j = seed % (SHA256_BLOCK_SIZE * 2); // Index in hex string
        temp[i++] = src[j];
    }
    temp[i] = '\0';
    
    strcpy(dest, temp);
    strcpy(input, temp); // Update input for next iteration
    return seed;
}

// Compute variable size hash
void variableSizeHash(const char *input, int size, char *final_hash) {
    // Validate input size
    if (size % 4 != 0 || size < 4 || size > MAX_BUFFER * 4) {
        fprintf(stderr, "Error: Size must be a multiple of 4 and within valid range\n");
        final_hash[0] = '\0';
        return;
    }

    SHA256_CTX ctx;
    BYTE hash[SHA256_BLOCK_SIZE];
    char hex_hash[SHA256_HEX_SIZE];
    char temp_input[MAX_BUFFER];
    char selected_chars[MAX_BUFFER];
    
    // Initialize input with input+size
    snprintf(temp_input, MAX_BUFFER, "%s+%d", input, size);

    int iterations = calculateIterations(size);
    BYTE hash_store[iterations][SHA256_BLOCK_SIZE];
    unsigned int seed = 0xab915;

    // Iterative hash computation
    for (int i = 0; i < iterations; i++) {
        printf("\nIteration %d:\nSeed: %u\nInput: %s\n", i + 1, seed, temp_input);
        
        sha256_init(&ctx);
        sha256_update(&ctx, temp_input, strlen(temp_input));
        sha256_final(&ctx, hash);
        
        hashToHex(hash, hex_hash);
        printf("Hash: %s\n", hex_hash);
        
        seed = select16HexChars(temp_input, selected_chars, hex_hash, seed);
        memcpy(hash_store[i], hash, SHA256_BLOCK_SIZE);
    }

    // Construct final hash
    int hex_chars_needed = size / 4;
    int collected_chars = 0;
    for (int i = 0; i < iterations && collected_chars < hex_chars_needed; i++) {
        char hex[SHA256_HEX_SIZE];
        hashToHex(hash_store[i], hex);
        
        int chars_to_copy = SHA256_BLOCK_SIZE * 2;
        if (collected_chars + chars_to_copy > hex_chars_needed) {
            chars_to_copy = hex_chars_needed - collected_chars;
        }
        
        strncpy(final_hash + collected_chars, hex, chars_to_copy);
        collected_chars += chars_to_copy;
    }
    
    final_hash[hex_chars_needed] = '\0';
}