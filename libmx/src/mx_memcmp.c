#include "../inc/libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n){
    const unsigned char *tmp1 = (unsigned char *)s1;
    const unsigned char *tmp2 = (unsigned char *)s2;
    if(n == 0) return 0;
    for(size_t i = 0; i < n; i++){
        if(tmp1[i] != tmp2[i]) return (tmp1[i] -  tmp2[i]);
        if (tmp1[i] == '\0' && tmp2[i] == '\0') return 0;
    }
    return (tmp1[0] -  tmp2[0]);
}
