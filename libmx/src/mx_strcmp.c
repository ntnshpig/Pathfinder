#include "../inc/libmx.h"

int mx_strcmp(const char *s1, const char *s2) {
    char c1, c2;

    do {
        c1 = *s1++;
        c2 = *s2++;
        if(c1 == '\0'){
            return c1 - c2;
        }
    } while (c1 == c2);

    return c1 - c2;
}
