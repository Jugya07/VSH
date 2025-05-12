#include <stdio.h>
#include "../include/vsh.h"

int main() {
    const char *input = "MyPassword123";
    int size = 64; // Desired hash size in bits
    char final_hash[1024];
    
    printf("Input: \"%s\", Hash Size: %d bits\n", input, size);
    
    variableSizeHash(input, size, final_hash);
    
    printf("Final Hash: %s\n", final_hash);
    
    return 0;
}