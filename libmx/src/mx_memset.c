#include "../inc/libmx.h"

void *mx_memset(void *b, int c, size_t len) {
    unsigned char *ptr = (unsigned char *)b;
    while (len > 0){
        len--;
        *ptr = (unsigned char)c;
        ptr++;
    }
    return b;
}
