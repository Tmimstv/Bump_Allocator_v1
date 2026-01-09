#include "arena.h"
#include <stddef.h>
#include <stdint.h>

// This is the pointer that 'al_alloc' will use
static Arena* global_arena_ptr = NULL;

// using this  to replace the other
void al_init(Arena* a) {
    global_arena_ptr = a;
}

void* al_alloc(size_t size) {
    if (!global_arena_ptr) return NULL;

    // 1. Calculate current position
    // Use uintptr_t to do safe math on the address
    uintptr_t current_addr = (uintptr_t)global_arena_ptr->base + global_arena_ptr->offset;

    // 2. Align the pointer to 16 bytes
    uintptr_t aligned_addr = (current_addr + 15) & ~15;

    // 3. Calculate new offset relative to base
    // This tracks how many bytes used in total
    uintptr_t new_offset = (aligned_addr - (uintptr_t)global_arena_ptr->base) + size;

    // 4. Bounds check against 'capacity' (matches your arena.h)
    if (new_offset > global_arena_ptr->capacity) {
        return NULL; 
    }

    // 5. Update state and return
    global_arena_ptr->offset = new_offset;
    return (void*)aligned_addr;
}
