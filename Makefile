# Makefile for Snow Simulation

# Compiler and flags
CC = gcc
CFLAGS = -Wall -O2
LIBS = -lSDL2 -lSDL2_image -levdev
SRC = christmasSnowGlobe.c  
OUTPUT = christmasSnowGlobe

# Default target: Build the program
all: check_deps $(OUTPUT)

# Compile the program
$(OUTPUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUTPUT) $(LIBS)

# Check for required libraries
check_deps:
	@which sdl2-config > /dev/null || (echo "Error: SDL2 library not found" && exit 1)
	@pkg-config --exists SDL2_image || (echo "Error: SDL2_image library not found" && exit 1)
	@pkg-config --exists libevdev || (echo "Error: libevdev library not found" && exit 1)

# Clean build artifacts
clean:
	rm -f $(OUTPUT)

# Run the program
run: $(OUTPUT)
	./$(OUTPUT) -w 720 -h 720 -e /dev/input/event0
