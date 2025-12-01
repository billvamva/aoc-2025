CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
LDFLAGS =
TARGET = main
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program and measure execution time
run: $(TARGET)
	@echo "Running $(TARGET)..."
	@start=$$(date +%s); ./$(TARGET); end=$$(date +%s); \
	 echo "Execution time: $$((end - start)) seconds"

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean run
