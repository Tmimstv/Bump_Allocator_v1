#include <stddef.h> //for size_t
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>


typedef struct {

void *base;
size_t capacity;
size_t offset;
} Arena;


bool arena_init(Arena *a, size_t size_in_pages);

void arena_destroy(Arena *a);

void arena_reset(Arena *a);

void* arena_alloc(Arena *a, size_t size);

size_t align_forward(size_t ptr, size_t align);


