#include "../inc/pathfinder.h"

void print_path(char *path, int **matrix, char **islands) {
    char **tmp = mx_strsplit(path, ',');
    int tmp_size = amount_of_el(tmp);
    int sum = 0;
    //Path
    mx_printstr("========================================\n");
    mx_printstr("Path: ");
    mx_printstr(tmp[0]);
    mx_printstr(" -> ");
    mx_printstr(tmp[tmp_size-1]);
    mx_printchar('\n');
    //Route
    mx_printstr("Route: ");
    for (int i = 0; i < tmp_size; i++){
        mx_printstr(tmp[i]);
        if(i >= 0 && i < tmp_size-1) mx_printstr(" -> ");
    }
    //Distance
    int first = get_index_in_strarr(islands, tmp[0]);
    int second = get_index_in_strarr(islands, tmp[1]);
    if(tmp_size == 2){
        mx_printstr("\nDistance: ");
        mx_printint(matrix[first][second]);
        mx_printstr("\n========================================\n");
    } else {
        mx_printstr("\nDistance: ");
        mx_printint(matrix[first][second]);
        sum+=matrix[first][second];
        for (int i = 1; i <tmp_size-1; i++){
            first = get_index_in_strarr(islands, tmp[i]);
            second = get_index_in_strarr(islands, tmp[i+1]);
            mx_printstr(" + ");
            sum+=matrix[first][second];
            mx_printint(matrix[first][second]);
        }
        mx_printstr(" = ");
        mx_printint(sum);
        mx_printstr("\n========================================\n");
    }
}
