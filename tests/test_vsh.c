#include <stdio.h>
#include <string.h>
#include "test_vsh.h"
#include "../include/vsh.h"

#define MAX_BUFFER 1024

// Test consistency: Same input produces same hash
int testConsistency(const char *input, int size) {
    char hash1[MAX_BUFFER];
    char hash2[MAX_BUFFER];
    
    variableSizeHash(input, size, hash1);
    variableSizeHash(input, size, hash2);
    
    return strcmp(hash1, hash2) == 0;
}

// Test avalanche effect: Small input change causes significant hash change
int testAvalanche(const char *input, int size) {
    char hash1[MAX_BUFFER];
    char hash2[MAX_BUFFER];
    char modified_input[MAX_BUFFER];
    
    strcpy(modified_input, input);
    modified_input[0] = input[0] + 1; // Change one character
    
    variableSizeHash(input, size, hash1);
    variableSizeHash(modified_input, size, hash2);
    
    int diff_count = 0;
    for (int i = 0; i < size / 4; i++) {
        if (hash1[i] != hash2[i]) diff_count++;
    }
    
    // Expect at least 40% of characters to differ
    return diff_count >= (size / 4) * 0.4;
}

// Run all tests
void runTests() {
    const char *input = "MyPassword123";
    int sizes[] = {16, 64, 128, 256};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    printf("Running Tests...\n");
    
    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];
        printf("\nTesting size %d bits:\n", size);
        
        printf("Consistency Test: %s\n", testConsistency(input, size) ? "Pass" : "Fail");
        printf("Avalanche Test: %s\n", testAvalanche(input, size) ? "Pass" : "Fail");
    }
}