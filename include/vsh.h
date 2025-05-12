#ifndef VSH_H
#define VSH_H

// Compute variable size hash of input string
// size: Desired hash size in bits (must be a multiple of 4)
// final_hash: Buffer to store the hex hash (must be at least size/4 + 1 bytes)
void variableSizeHash(const char *input, int size, char *final_hash);

#endif // VSH_H