#include "../inc/libmx.h"

int mx_abs(int num) {
    return num < 0 ? -num : num;
}

char *mx_itoa(int number) {
    int length = 0;

    bool isNegative = false;
    if (number < 0) isNegative = true;

    for (int i = number; i > 0 || i < 0; i /= 10) length++;

    char *result = mx_strnew(length);
    if(result == NULL) return NULL;
    if (number == 0) return mx_strcpy(result, "0");
    
    int temp = number;
    for (int counter = 0; counter < length; counter++) {
        result[counter] = mx_abs(temp % 10) + '0';
        temp /= 10;
    }

    mx_str_reverse(result);
    return isNegative ? mx_strjoin("-", result) : result;
}
