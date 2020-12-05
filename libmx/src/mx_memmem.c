#include "../inc/libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {
    unsigned char *tmp1 = (unsigned char *)big;
    unsigned char *tmp2 = (unsigned char *)little;
    if(big_len <= 0  || little_len <= 0 || big_len < little_len) return NULL; 
    while(*tmp1){
      if(mx_memcmp(tmp1, tmp2, little_len-1) == 0){
        return tmp1;
      }
      tmp1++;
    }  
    return NULL;
}
