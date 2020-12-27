#include "../inc/pathfinder.h"

void way_to_str(t_node **res_paths, char **path, int size_path){
    t_node **tmp_res = res_paths; 
    for(int a = 0; a < size_path; a++){//Way to str
        char *tmp_str = mx_strdup(mx_itoa(res_paths[a]->all_way));
        tmp_str = mx_strjoin(tmp_str, "|");
        while(tmp_res[a] != NULL){
        tmp_str = mx_strjoin(tmp_str, tmp_res[a]->name);
        tmp_str = mx_strjoin(tmp_str, ",");
        tmp_res[a] = tmp_res[a]->parent;
        }
        path[a] = tmp_str;
    }
    for(int a = 0; a < size_path; a++){//Reverce way
        char **tmp_arr1 = mx_strsplit(path[a], '|');
        char **tmp_arr2 = mx_strsplit(tmp_arr1[1], ',');
        char *tmp_str = NULL;
        for(int i = amount_of_el(tmp_arr2)-1; i >= 0; i--){
            tmp_str = mx_strjoin( tmp_str, tmp_arr2[i]);
            tmp_str = mx_strjoin( tmp_str, ",");
        }
        tmp_str = mx_strjoin( tmp_str, "|");
        tmp_str = mx_strjoin( tmp_str, tmp_arr1[0]);
        path[a] = tmp_str;
    }
}
