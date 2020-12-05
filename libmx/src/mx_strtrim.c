#include "../inc/libmx.h"

char *mx_strtrim(const char *str) {
    if(!str) return NULL;
    int space_before = 0;
    int space_after = 0;
    for (int i = 0; mx_isspace(str[i]); i++) {
        space_before++;
    }
    for (int i = mx_strlen(str); mx_isspace(str[i-1]); i--) {
        space_after++;
    }
    int new_size = mx_strlen(str) - (space_before + space_after);
    return mx_strndup(&str[space_before], new_size);
}

/*char *mx_strtrim1(const char *str) {
    if(!str) return NULL;
    int size = mx_strlen(str);
    int space_before = 0;
    int space_after = 0;
    while (mx_isspace(str[space_before])){
        space_before++;
    }
    while (mx_isspace(str[size - 1 - space_after])){
        space_after++;
    }
    int new_size = size - (space_before + space_after);
    return mx_strndup(&str[space_before], new_size);
}

int main(){
    printf("%s\n", mx_strtrim("   \f\f\f  \f    My name     ...   is  Neo  \t   \n "));
    printf("%s\n", mx_strtrim1("     \f\f\f \f   My name     ...   is  Neo  \t   \n "));
}
*/
