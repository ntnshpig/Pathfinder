#include "../inc/libmx.h"

char *mx_strnew(const int size) {
    char *string = (char *)malloc((size + 1) * sizeof(char));
    if(string == NULL || size < 0) return NULL;

    for(int i = 0; i < size + 1; ++i) {
        string[i] = '\0';
    }

    return string;
}
