#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>
#include "arena.h"





bool arena_init(Arena *a, size_t size_in_pages){

	size_t pagesize = (size_t)sysconf(_SC_PAGESIZE);
	printf("System page size: %zu bytes\n", pagesize);
	size_t total_size = size_in_pages * pagesize;

	//using mmap to get buffer
	//mapping memory
	a->base = mmap(NULL, (total_size), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if(a->base == MAP_FAILED){
		perror("mmap");
		return false;
	}

	a->capacity = total_size;
	a->offset = 0; //start at the beginning
	return true;
}

void arena_destroy(Arena *a){
	if(a->base){
		munmap(a->base, a->capacity);
		a->base = NULL;
		a->capacity = 0;
		a->offset = 0;
	}
}

void arena_reset(Arena *a){
	a->offset = 0;
}


void* arena_alloc(Arena *a, size_t size) {
 
	size_t aligned_size = align_forward(size, 8);
   // 1. Safety Check: do we have enough capacity?
    if (a->offset + aligned_size > a->capacity) {
        return NULL;
    }

    // 2. Calculate the pointer to return
    // Hint: Cast a->base to (uint8_t *) so the + operator works in bytes
    void *ptr = (uint8_t *)a->base + a->offset;

    // 3. Move the "cursor" forward
    a->offset += aligned_size;

    // 4. Return the pointer
    return ptr;
}

// A common helper to align a size upward to the nearest multiple of 'align'
// 'align' must be a power of 2 (like 8 or 16)
size_t align_forward(size_t ptr, size_t align) {
    return (ptr + (align - 1)) & ~(align - 1);
}

