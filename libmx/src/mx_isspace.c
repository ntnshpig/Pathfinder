#include "../inc/libmx.h"

bool mx_isspace(char c) {
    if (c == ' ' || c == '\t' || c == '\n' ) {
        return true;
    }
    else if (c == '\v' || c == '\f' || c == '\r') {
        return true;
    }
    else {
        return false;
    }
}
