#include "../inc/libmx.h"

void *mx_memchr(const void *s, int c, size_t n){
    const unsigned char *temp = (unsigned char *)s;
    if(n == 0) return 0;
    for(size_t i = 0; i < n; i++){
        if(temp[i] == c) return (char*)&temp[i];
    }
    return 0;
}
