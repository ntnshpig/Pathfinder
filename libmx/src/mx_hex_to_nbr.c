#include "../inc/libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
	if (hex == NULL) return 0;
	int j = 0;
	while (hex[j] != '\0') j++;
	unsigned long result = 0;
	unsigned long dec = 1;
	for (int i = j - 1; i >= 0; i--) {
		if (mx_isdigit(hex[i])) {
			result += ((hex[i] - 48) * dec);
			dec *= 16;
		}
		if (mx_isalpha(hex[i])) {
			if (mx_isupper(hex[i])) {
				result += ((hex[i] - 55) * dec);
				dec *= 16;
			}
			else {
				result += ((hex[i] - 87) * dec);
				dec *= 16;
			}
		}
	}
	return result;
}
