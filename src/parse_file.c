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

    //Create and fill matrix by -1
    int **matrix = (int **)malloc((first_num_int*first_num_int)*sizeof(int));
    for(int i = 0; i < first_num_int; i++){
        matrix[i] = (int*)malloc((first_num_int) * sizeof(int));
    }
    for(int i = 0; i < first_num_int; i++){
        for(int j = 0; j < first_num_int; j++){
            matrix[i][j] = -1;
        }   
    }

    //Fill matrix and check for dublicats
    for(int i = 0; str_without_first_num[i]; i++) {
        char *from = mx_strndup(str_without_first_num[i], mx_get_char_index(str_without_first_num[i], '-'));
        char *to = mx_strndup(&str_without_first_num[i][mx_get_char_index(str_without_first_num[i], '-')+1], mx_get_char_index(str_without_first_num[i], ',') - mx_strlen(from) - 1);
        char *bridge_num = mx_strdup(&str_without_first_num[i][mx_get_char_index(str_without_first_num[i], ',')+1]);
        int first_index = get_index_in_strarr(islands, from);
        int second_index = get_index_in_strarr(islands, to);////000000
        if(matrix[first_index][second_index] == -1 && matrix[second_index][first_index] == -1){
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
    
    //Only for know right memory
    int size_path = 0;
    for(int islands_i = 0; islands_i < first_num_int; islands_i++) {
        for(int islands_j = islands_i; islands_j < first_num_int; islands_j++) {
            if(islands_i != islands_j) {                
                t_node **a = pathfinder_alg(matrix, islands, islands_i, islands_j, first_num_int);
                for(int j = 0; a[j] != NULL; j++) {
                    size_path++;
                } 
            }
        }   
    }
    
    //Create result paths graph and fill by NULL
    t_node **res_paths = (t_node **) malloc((size_path + 1) * sizeof(t_node *));
    for(int j = 0; j < size_path; j++) res_paths[j] = NULL;
    
    //Doing algorithm
    size_path = 0;
    for(int islands_i = 0; islands_i < first_num_int; islands_i++) {
        for(int islands_j = islands_i; islands_j < first_num_int; islands_j++) {
            if(islands_i != islands_j) {
                t_node **a = pathfinder_alg(matrix, islands, islands_i, islands_j, first_num_int);
                for(int j = 0; a[j] != NULL; j++) {
                    res_paths[size_path] = (t_node*)malloc(sizeof(t_node));
                    res_paths[size_path] = a[j];
                    size_path++;
                }
            }
        }   
    }
    
    //Convert way from graph to str
    char **path = (char **)malloc((size_path*size_path)*sizeof(char));
    way_to_str(res_paths, path, size_path);

    //Sort and output the path
    int size_one_way = 0;
    char **res = (char **)malloc((__INT_MAX__/100)*sizeof(char));
    for(int j = 0; j < first_num_int; j++){
        for(int z = j; z < first_num_int; z++){
            for(int a = 0; a < size_path; a++){
                char **tmp_without_num = mx_strsplit(path[a], '|');
                char **tmp = mx_strsplit(tmp_without_num[0], ',');
                if(mx_strcmp(tmp[0], islands[j]) == 0 && mx_strcmp(tmp[amount_of_el(tmp)-1], islands[z]) == 0){
                    res[size_one_way] = mx_strdup(path[a]);
                    size_one_way++;
                }
            }
            if(size_one_way != 0){
                sort_path_all(res, islands, matrix, (unsigned long)size_one_way);
            }
            size_one_way = 0;
        }
    }
}
