#include "../inc/libmx.h"

bool mx_isupper(int c) {
    if (c >= 65 && c <= 90) {
        return true;
    } 
    else {
        return false;
    }
}
