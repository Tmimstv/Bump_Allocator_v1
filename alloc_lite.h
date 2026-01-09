#include <stddef.h>
#include <stdint.h>


void* al_alloc(size_t size);
void al_reset(); //resets bump pointer to the beginning
void al_init(Arena* a);

