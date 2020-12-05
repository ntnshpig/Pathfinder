#include "../inc/libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    if (!str || !sub) return -2;
    bool answ = false;
    for (int i = 0; str[i]; i++) {
        if (str[i] == sub[0]) {
            for(int j = 0; sub[j]; j++) {
                if(sub[j] != str[j+i]){
                    answ = false;
                    break;
                }
                answ = true;
            }
        }
        if(answ == true) return i;
    }
    return -1;
}
