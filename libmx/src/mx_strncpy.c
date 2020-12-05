#include "../inc/libmx.h"

char *mx_strncpy(char *dst, const char *src, int len) {
   if(!src) return NULL;
   for (int i = 0; i < len; i++) {
        if (dst) {
            if(src) {
               dst[i] = src[i];
            } else {
               dst[i] = '\n';
           }
        } else {
           return dst;
        }
   }
   return dst;
}
