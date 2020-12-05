#include "../inc/libmx.h"

void *mx_memrchr(const void *s, int c, size_t n){
    const unsigned char *temp = (unsigned char *)s;
    if(n == 0) return 0;
    for(size_t i = n; i > 0; i--){
        if(temp[i] == c) return (char*)&temp[i];
    }
    return 0;
}
