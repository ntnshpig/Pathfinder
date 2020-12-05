#include "../inc/libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    if (sub == NULL || str == NULL) return -1;
    if(mx_strcmp(sub, "") == 0) return 0;
    int counter = 0;
    if (mx_strlen(sub) <= mx_strlen(str)) {
         while (*str) {
            if (mx_strncmp(str, sub, mx_strlen(sub)) == 0) counter++;
            str++;
        }
    }
    return counter;
}
