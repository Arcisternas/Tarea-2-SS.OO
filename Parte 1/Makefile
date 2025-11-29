CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -std=c11
TARGET = main
SRCS = main.c barrera.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean run rebuild

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c barrera.h
barrera.o: barrera.c barrera.h

clean:
	rm -f $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)

rebuild: clean all