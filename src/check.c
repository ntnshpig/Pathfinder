#include "../inc/pathfinder.h"

bool correct_digit(const char *num){
    if(mx_strcmp(num, "") == 0) return false;
    for (int i = 0; i < mx_strlen(num); i++)
        if (!mx_isdigit(num[i])) return false;

    if(mx_atoi(num) < 0) return false;
    return true;
}

bool correct_word(const char *word) {
    for (int i = 0; i < mx_strlen(word); i++)
        if (!mx_isalpha(word[i])) return false;
    return true;
}

bool correct_line(const char *from, const char *to, const char *bridge) {
    if (!from || !to || !bridge) return false;

    if(!correct_word(from)) return false;
    if(!correct_word(to)) return false;
    if(!correct_digit(bridge)) return false;
    
    if (mx_strcmp(from, to) == 0) return false;

    return true;
}

void check_extra_enter(char *str) {//Enter in the end of file
    int num_n = 0;
    for(int i = 0; i < mx_strlen(str)-1; i++) {
        if(str[i] == '\n') num_n++;
        if(str[i] == '\n' && !mx_isalpha(str[i+1])) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(num_n+1)); 
            mx_printerr(" is not valid\n");
            exit(0);
        }
    }
}
