#ifndef TEST_VSH_H
#define TEST_VSH_H

// Run all test cases for the variable size hash
void runTests(void);

// Test consistency: Same input produces same hash
int testConsistency(const char *input, int size);

// Test avalanche effect: Small input change causes significant hash change
int testAvalanche(const char *input, int size);

#endif // TEST_VSH_H