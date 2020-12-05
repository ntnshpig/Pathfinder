#include "../inc/libmx.h"

void mx_printint(int n) {
	char str[50];
    long temp_n = n;
	int sign, i = 0;
	if (n == 0) mx_printchar('0');
	if ((sign = n) < 0) temp_n = temp_n * -1;

	while (temp_n != 0) {
		str[i++] = temp_n % 10 + '0';
		temp_n = temp_n / 10;
	}

	if (sign < 0) str[i++] = '-';
	for (int j = i-1; j>=0; --j) 
             mx_printchar(str[j]); 
}
