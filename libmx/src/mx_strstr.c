#include "../inc/libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    if(mx_strlen(needle) == 0) return (char *)haystack;
    char *tmp = mx_strchr(haystack, needle[0]);
    while(tmp != '\0'){
      if(mx_strncmp(tmp, needle, mx_strlen(needle)) == 0){
        return (char *) tmp;
      }
      tmp++;
    }
    return NULL;
}
