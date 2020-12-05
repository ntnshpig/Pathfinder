#include "../inc/libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    size_t size = mx_strlen(s1);
    if (n < size) size = n;
    char *result = mx_strnew(size);
    if(result == NULL) return NULL;
    return (mx_strncpy(result, s1, size));
}
