#include "../inc/libmx.h"

char *mx_strdup(const char *str) {
    int size = mx_strlen(str);
    char *result = mx_strnew(size);
    if(result == NULL) return NULL;
    return (mx_strcpy(result,str));
}
