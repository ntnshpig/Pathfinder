#include "../inc/libmx.h"

void mx_swap_char(char *s1, char *s2) {
    char temp1 = *s1;
    char temp2 = *s2;
    *s1 = temp2;
    *s2 = temp1;
}
