
CC = gcc
CFLAGS = -I"./include" -Wall -Wextra -std=c99
SRC = "src/main.c" "src/Algoritmos.c"
TARGET = sim.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)

clean:
	del /Q $(TARGET) 2>nul
