#include "../inc/libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len){
    unsigned char *tmp1 = (unsigned char *)src;
    unsigned char *tmp2 = malloc(len);
    for (size_t i = 0; i < len; i++) tmp2[i] = tmp1[i];
    dst = mx_memcpy(dst, tmp2, len);
    free(tmp2);
    return dst;
}
