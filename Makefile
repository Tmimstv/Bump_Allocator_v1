CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = Bump_Allocator_v1


#default make command
all: $(TARGET)

$(TARGET): arena.c alloc_lite.c main.c alloc_lite.h arena.h
	$(CC) $(CFLAGS) arena.c alloc_lite.c main.c -o $(TARGET)

#cleaning up
clean:
	rm -f $(TARGET)

