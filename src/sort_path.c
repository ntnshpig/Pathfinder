#include "../inc/pathfinder.h"

void sort_path_all(char **path, char **islands, int **arr, unsigned long size){
    //Sort by distance
    for(unsigned long i = 0; i < size; i++){
        for(unsigned long j = 0; j < size-1; j++){
            char **tmp1 = mx_strsplit(path[j], '|');
            char **tmp2 = mx_strsplit(path[j+1], '|');
            if(mx_atoi(tmp1[1]) > mx_atoi(tmp2[1])){
                char *tmp_path = mx_strdup(path[j]);
                path[j] = mx_strdup(path[j+1]);
                path[j+1] = mx_strdup(tmp_path);
            }
        }
    }
    
    //Write only minimum paths
    char **tmp_num = mx_strsplit(path[0], '|');
    char **only_min = (char **)malloc((size*size)*sizeof(char));
    int size_min = 0;
    for(unsigned long i = 0; i < size; i++){
        char **tmp = mx_strsplit(path[i], '|');
        if(mx_atoi(tmp_num[1]) != mx_atoi(tmp[1]))
            break;
        only_min[size_min] = mx_strdup(path[i]);
        size_min++;
    }
    
    //Sort by names
    sort_path_names(only_min, islands, size_min);

    //Output
    for(int  i = 0; i < size_min; i++){
        char **tmp = mx_strsplit(only_min[i], '|');
        print_path(tmp[0], arr, islands);
    }
}

void sort_path_names(char **path, char **islands, unsigned long size){
    for(unsigned long i = 0; i < size; i++){
        for(unsigned long j = 0; j < size-1; j++){
            char **tmp_without_num1 = mx_strsplit(path[j], '|');
            char **tmp_without_num2 = mx_strsplit(path[j+1], '|');
            char **tmp1 = mx_strsplit(tmp_without_num1[0], ',');
            char **tmp2 = mx_strsplit(tmp_without_num2[0], ',');
            int z = 1;
            while(true){
                if(!tmp1[z] || !tmp2[z]) break;
                if(get_index_in_strarr(islands, tmp1[z]) > get_index_in_strarr(islands, tmp2[z]) && mx_strcmp(tmp1[z-1], tmp2[z-1]) == 0) {
                    char *tmp_path = mx_strdup(path[j]);
                    path[j] = mx_strdup(path[j+1]);
                    path[j+1] = mx_strdup(tmp_path);
                    break;
                }
                z++;
            }
        }
    }
}

int amount_of_el(char **arr) {
    int res = 0;
    while(arr[res]){
        res++;
    }
    return res;
}
