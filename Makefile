# Makefile for Helheim Engine 2D
CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lm

# Source files
SOURCES = main.c globals.c entity.c particle.c inventory.c collision.c tile.c rendering.c input.c gameplay.c menu.c utils.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = HelheimEngine2D.exe

# Default target
all: $(EXECUTABLE)

# Build the executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	del /q *.o *.exe

# Run the game
run: $(EXECUTABLE)
	$(EXECUTABLE)

.PHONY: all clean run
