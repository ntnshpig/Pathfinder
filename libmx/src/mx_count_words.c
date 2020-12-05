#include "../inc/libmx.h"

int mx_count_words(const char *str, char c) {
    int word = 0;
    if (!str) return -1;

    while (*str != '\0') {
        if (*str == c) {
            while (*str == c && *str != '\0')
                str++;
        }
        if (*str != c && *str != '\0') {
            word++;
            while (*str != c && *str != '\0')
                str++;
        }
    }
    return word;
}
