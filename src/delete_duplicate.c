#include "../inc/pathfinder.h"

char **without_duplicate(char **arr, int lines, int dif_isl){//Delete dublicate in islands
    char **result = (char **)malloc(dif_isl*9);
    int a = 1;
    result[0] = arr[0];
    for(int i = 0; i < (lines*2); i++){
        if(get_index_in_strarr(result, arr[i]) == -1) {
            result[a] = arr[i];
            a++;
        }
        if(a > dif_isl){       
            mx_printerr("error: invalid number of islands\n");
            exit(0);
        }
    }
    if(a < dif_isl) {
        mx_printerr("error: invalid number of islands\n");
        exit(0);
    }
    result[a] = arr[(lines*2)-1];
    return result;
}
