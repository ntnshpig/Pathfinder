#include "../inc/pathfinder.h"

int get_index_in_strarr(char **arr, char *sub){
    for(int i = 0; arr[i]; i++){
        if(mx_strcmp(arr[i], sub) == 0) return i;
    }
    return -1;
}
