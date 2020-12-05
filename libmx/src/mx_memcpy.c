#include "../inc/libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
    unsigned char *tmp1 = (unsigned char *)src;
    unsigned char *tmp2 = (unsigned char *)dst;
    for (size_t i = 0; i < n; i++) tmp2[i] = tmp1[i];
    return dst;
}
