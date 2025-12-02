# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O1 -g -fsanitize=address
LDFLAGS = -fsanitize=address
TARGET = main

# Automatically detect source and object files
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

# Default target
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Object file build rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program and print execution time in milliseconds
run: $(TARGET)
	@echo "Running $(TARGET)..."
	@start=$$(date +%s%3N); \
	 ./$(TARGET); \
	 end=$$(date +%s%3N); \
	 elapsed=$$((end - start)); \
	 echo "\nExecution time: $${elapsed} ms"

# Debug build (with sanitizer)
debug: CFLAGS = -Wall -Wextra -O0 -g -fsanitize=address
debug: LDFLAGS = -fsanitize=address
debug: clean $(TARGET)

# Release build (optimized, no sanitizer)
release: CFLAGS = -Wall -Wextra -O2
release: LDFLAGS =
release: clean $(TARGET)

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean run debug release
