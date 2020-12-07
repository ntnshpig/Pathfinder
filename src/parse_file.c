#include "../inc/pathfinder.h"

void parse_file(const char *file_name) {
    char *str_all_file = mx_file_to_str(file_name);

    //First number
    if(str_all_file[0] == '\n'){
        mx_printerr("error: line 1 is not valid\n");
        exit(0);
    }
    char *first_num_ch = mx_strndup(str_all_file, mx_get_char_index(str_all_file, '\n'));
    int first_num_int = -1;
    if(correct_digit(first_num_ch) ==  true && mx_atoi(first_num_ch) <= __INT_MAX__) {
        first_num_int = mx_atoi(first_num_ch);
    } else {
        mx_printerr("error: line 1 is not valid\n");
        exit(0);
    }

    //Split for a lines without first num
    char **str_without_first_num = mx_strsplit(&str_all_file[mx_get_char_index(str_all_file, '\n')+1], '\n');
    
    //Amount of lines
    int count_lines = 0;
    while (str_without_first_num[count_lines] != NULL) count_lines++;

    //Split for a Islands
    char **islands = (char **)malloc((count_lines*9)*2);
    int a = 0;
    unsigned long sum_km = 0;
    for(int i = 0; str_without_first_num[i]; i++) {
        char *from = mx_strndup(str_without_first_num[i], mx_get_char_index(str_without_first_num[i], '-'));
        islands[a] = mx_strdup(from);
        a++;
        char *to = mx_strndup(&str_without_first_num[i][mx_get_char_index(str_without_first_num[i], '-')+1], mx_get_char_index(str_without_first_num[i], ',') - mx_strlen(from) - 1);
        islands[a] = mx_strdup(to);
        a++;
        char *bridge_num = mx_strdup(&str_without_first_num[i][mx_get_char_index(str_without_first_num[i], ',')+1]);
        if(correct_line(from, to, bridge_num) == false) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i+2)); 
            mx_printerr(" is not valid\n");
            exit(0);
        }
        sum_km += mx_atoi(bridge_num);
    }

    //Check for extra new line in file
    check_extra_enter(str_all_file);

    //Delete dublicate and check for correct islands
    islands = without_duplicate(islands, count_lines, first_num_int);

    //Fill matrix by zero
    int **matrix = (int **)malloc((first_num_int*first_num_int)*sizeof(int));
    for(int i = 0; i < first_num_int; i++){
        matrix[i] = (int*)malloc((first_num_int) * sizeof(int));
    }
    for(int i = 0; i < first_num_int; i++){
        for(int j = 0; j < first_num_int; j++){
            matrix[i][j] = 0;
        }   
    }

    //Fill matrix and check for dublicats
    for(int i = 0; str_without_first_num[i]; i++) {
        char *from = mx_strndup(str_without_first_num[i], mx_get_char_index(str_without_first_num[i], '-'));
        char *to = mx_strndup(&str_without_first_num[i][mx_get_char_index(str_without_first_num[i], '-')+1], mx_get_char_index(str_without_first_num[i], ',') - mx_strlen(from) - 1);
        char *bridge_num = mx_strdup(&str_without_first_num[i][mx_get_char_index(str_without_first_num[i], ',')+1]);
        int first_index = get_index_in_strarr(islands, from);
        int second_index = get_index_in_strarr(islands, to);
        if(matrix[first_index][second_index] == 0 && matrix[second_index][first_index] == 0){
        matrix[first_index][second_index] = mx_atoi(bridge_num);
        matrix[second_index][first_index] = mx_atoi(bridge_num);
        } else {
            mx_printerr("error: duplicate bridges\n");
            exit(0);
        }
    }

    //Check for too long distance
    if(sum_km > __INT_MAX__){
        mx_printerr("error: sum of bridges lengths is too big\n");
        exit(0);
    }

    //Pathfinder  i = from wich island
    for(int i = 0; i < first_num_int; i++){
        find_path(islands, matrix, i, first_num_int);
    }
}
