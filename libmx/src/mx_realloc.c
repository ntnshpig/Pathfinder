#include "../inc/libmx.h"

void *mx_realloc(void *ptr, size_t size){
    size_t old_size;
    if (ptr == 0) return malloc(size);
    old_size = malloc_size(ptr);
    if (size <= old_size) return ptr;   
    void *new_ptr = malloc(size);
    mx_memcpy(new_ptr, ptr, old_size);
    free(ptr);
    return new_ptr;
}
