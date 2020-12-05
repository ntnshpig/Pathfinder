#include "../inc/libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if(!str || !sub || !replace) return NULL;
    if(!*sub) return (char*)str;
    char *result = NULL;
    while(*str != '\0') {
        int j = 0;
        if (mx_strncmp(str, sub, mx_strlen(sub)) == 0) {
            result = mx_strjoin(result, replace);
            str += mx_strlen(sub);
            continue;
        }
        char c = str[j];
        result = mx_strjoin(result, &c);
        str++;
    }
    return result;
}
