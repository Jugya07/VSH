CC = gcc
CFLAGS = -Wall -Iinclude -Itests
LDFLAGS =

SRC = src/vsh.c src/sha256/sha256.c
TEST_SRC = tests/test_vsh.c tests/test_main.c
EXAMPLE_SRC = examples/example.c
OBJ = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)
EXAMPLE_OBJ = $(EXAMPLE_SRC:.c=.o)
EXEC = build/vsh_test
EXAMPLE_EXEC = build/vsh_example

# Ensure build directory exists
$(shell mkdir -p build)

all: $(EXEC) $(EXAMPLE_EXEC)

$(EXEC): $(OBJ) $(TEST_OBJ)
	$(CC) $(OBJ) $(TEST_OBJ) $(LDFLAGS) -o $@
	@echo "Built test binary: $@"

$(EXAMPLE_EXEC): $(OBJ) $(EXAMPLE_OBJ)
	$(CC) $(OBJ) $(EXAMPLE_OBJ) $(LDFLAGS) -o $@
	@echo "Built example binary: $@"

# Object file rules
src/vsh.o: src/vsh.c include/vsh.h
	$(CC) $(CFLAGS) -c $< -o $@

src/sha256/sha256.o: src/sha256/sha256.c src/sha256/sha256.h
	$(CC) $(CFLAGS) -c $< -o $@

tests/test_vsh.o: tests/test_vsh.c tests/test_vsh.h include/vsh.h
	$(CC) $(CFLAGS) -c $< -o $@

tests/test_main.o: tests/test_main.c tests/test_vsh.h
	$(CC) $(CFLAGS) -c $< -o $@

examples/example.o: examples/example.c include/vsh.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(EXAMPLE_OBJ) $(EXEC) $(EXAMPLE_EXEC)
	@echo "Cleaned build artifacts"

test: $(EXEC)
	@echo "Running tests..."
	./$(EXEC)

example: $(EXAMPLE_EXEC)
	@echo "Running example..."
	./$(EXAMPLE_EXEC)

.PHONY: all clean test example