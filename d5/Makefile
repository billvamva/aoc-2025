CC = gcc
CFLAGS = -Wall -Wextra -O0 -g -Ilib -fsanitize=address,undefined
LDFLAGS = -fsanitize=address,undefined
TARGET = main

# All C files anywhere
SRCS := $(wildcard *.c) $(wildcard lib/*.c)
# All headers
HDRS := $(wildcard lib/*.h)

# Object files from both root and lib/
OBJS := $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Every object depends on its own .c and any header in lib/
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	 time ./$(TARGET); 

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean run
