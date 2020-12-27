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
    int *path_to_num = (int *)malloc((size)*sizeof(int));
    for(unsigned long i = 0; i < size; i++){
        path_to_num[i] = 10;
    }
    for(unsigned long i = 0; i < size; i++){
        char **tmp_without_num = mx_strsplit(path[i], '|');
        char **tmp = mx_strsplit(tmp_without_num[0], ',');
        for(int j =0; tmp[j]; j++){
            path_to_num[i] += get_index_in_strarr(islands, tmp[j]);
            path_to_num[i] *= 10;
        }
    }
    for(unsigned long i = 0; i < size; i++){
        for(unsigned long j = 0; j < size-1; j++){
            if(amount_of_num(path_to_num[j]) < amount_of_num(path_to_num[j+1])){
                int tmp = path_to_num[j];
                path_to_num[j] = path_to_num[j+1];
                path_to_num[j+1] = tmp;
                char *tmp_path = mx_strdup(path[j]);
                path[j] = mx_strdup(path[j+1]);
                path[j+1] = mx_strdup(tmp_path);
            }
            if(amount_of_num(path_to_num[j]) == amount_of_num(path_to_num[j+1])){
                if(path_to_num[j] > path_to_num[j+1]){
                    int tmp = path_to_num[j];
                    path_to_num[j] = path_to_num[j+1];
                    path_to_num[j+1] = tmp;
                    char *tmp_path = mx_strdup(path[j]);
                    path[j] = mx_strdup(path[j+1]);
                    path[j+1] = mx_strdup(tmp_path);
                }
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

int amount_of_num(int num) {
    int cpy_num = num;
    int res = 0;
    do {
        res++;
        cpy_num /=10;
    } while (cpy_num  != 0);
    return res;
}
