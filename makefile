# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Iinclude -Wall -Wextra

# Source files
SRC = encode.c bemoji.c

# Output executable
TARGET = bemoji

# Build rules
all: $(TARGET)

$(TARGET): $(SRC:.c=.o)
	$(CC) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f *.o $(TARGET)

install:
	cp $(TARGET) ~/.local/bin/$(TARGET)

remove:
	rm ~/.local/bin/$(TARGET)

# Phony targets
.PHONY: all clean

