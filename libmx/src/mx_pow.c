#include "../inc/libmx.h"

double mx_pow(double n, unsigned int pow) {
    if(pow == 0) return 1;
    double result = 1;
    for (unsigned int i = 1; i <= pow; i++) {
        result *= n;
    }
    return result;
}
