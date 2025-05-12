# Variable Size Hashing Algorithm

This repository contains the implementation of a variable size hashing algorithm based on SHA-256, developed as a final year college project. The algorithm produces hash outputs of user-specified lengths (in multiples of 4 bits) by iteratively computing SHA-256 hashes and selecting hexadecimal characters.

## Features
- Configurable hash sizes (e.g., 16, 64, 128, 256 bits).
- Built on SHA-256 for cryptographic security.
- Modular codebase with separate core, tests, and examples.
- Includes a LaTeX thesis in the `docs` folder.

## File Structure
```
variable-size-hash/
├── include/          # Public headers
├── src/              # Core implementation
├── tests/            # Test suite
├── examples/         # Example usage
├── docs/             # Thesis and documentation
├── build/            # Compiled binaries
├── Makefile          # Build automation
├── README.md         # This file
├── LICENSE           # MIT License
└── .gitignore        # Ignored files
```

## Prerequisites
- GCC or compatible C compiler
- SHA-256 library (included in `src/sha256/`; ensure `sha256.h` and `sha256.c` are provided)

## Build and Run
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/variable-size-hash.git
   cd variable-size-hash
   ```
2. Build the project:
   ```bash
   make
   ```
3. Run tests:
   ```bash
   make test
   ```
4. Run example:
   ```bash
   make example
   ```

## Usage
Include `vsh.h` in your project and link against `vsh.c` and `sha256.c`. Example:
```c
#include "vsh.h"

int main() {
    char hash[1024];
    variableSizeHash("MyPassword123", 64, hash);
    printf("Hash: %s\n", hash);
    return 0;
}
```

## License
This project is licensed under the MIT License. See `LICENSE` for details.

## Contact
For questions, contact [Your Name] at [Your Email].