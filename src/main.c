#include "../inc/pathfinder.h"

bool correct_digit(const char *num){
    for (int i = 0; i < mx_strlen(num); i++)
        if (!mx_isdigit(num[i])) return false;

    if(mx_atoi(num) < 0 || mx_atoi(num) > __INT_MAX__) return false;
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

int get_index_in_strarr(char **arr, char *sub){
    for(int i = 0; arr[i]; i++){
        if(mx_strcmp(arr[i], sub) == 0) return i;
    }
    return -1;
}

char **without_dublicat(char **arr, int lines, int dif_isl){
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
            exit(-1);
        }
    }
    result[a] = arr[(lines*2)-1];
    return result;
}

void find_path(char **islands, int **a, int begin_index, int size){
    int min_dist[size]; //minimal distance
    int visited_node[size]; //visited peaks
    int temp, minindex, min;
    //Initialization
    for (int i = 0; i<size; i++) {
        min_dist[i] = 2147483647;
        visited_node[i] = 1;
    }
    min_dist[begin_index] = 0;
    do { //Algorothm step
        minindex = 2147483647;
        min = 2147483647;
        for (int i = 0; i<size; i++) { // Если вершину ещё не обошли и вес меньше min
            if ((visited_node[i] == 1) && (min_dist[i]<min)) { // Переприсваиваем значения
                min = min_dist[i];
                minindex = i;
            }
        }
        // Добавляем найденный минимальный вес
        // к текущему весу вершины
        // и сравниваем с текущим минимальным весом вершины
        if (minindex != 2147483647) {
        for (int i = 0; i<size; i++) {
            if (a[minindex][i] > 0) {
                temp = min + a[minindex][i];
                if (temp < min_dist[i]) {
                    min_dist[i] = temp;
                }
            }
        }
        visited_node[minindex] = 0;
        }
    } while (minindex < 2147483647);
    // Вывод кратчайших расстояний до вершин
    //if(min_dist[end_index] == 0) return;
    /*printf("\nКратчайшие расстояния до вершин: \n");
    for (int i = 0; i<size; i++){
        if(min_dist[i] == 2147483647) continue;
        printf("From %s to %s: %d\n", islands[begin_index], islands[i], min_dist[i]);
    }*/

    
    for(int i = begin_index; i < size; i++){
    int end = i;
    int end_index = end;
    if(min_dist[end_index] == 0 || min_dist[end_index] == 2147483647) continue;
    // Восстановление пути
    int ver[size]; // массив посещенных вершин
    ver[0] = end + 1; // начальный элемент - конечная вершина
    int k = 1; // Количество вершин для пути
    int weight = min_dist[end]; // вес конечной вершины

    while (end != begin_index) // пока не дошли до начальной вершины
    {
        for (int i = 0; i<size; i++) // просматриваем все вершины
        if (a[i][end] != 0)  { // если связь есть
            int temp = weight - a[i][end]; // определяем вес пути из предыдущей вершины
            if (temp == min_dist[i]) {// если вес совпал с рассчитанным значит из этой вершины и был переход
                weight = temp; // сохраняем новый вес
                end = i;       // сохраняем предыдущую вершину
                ver[k] = i + 1; // и записываем ее в массив
                k++;
            }
        }
    }

    // Вывод пути
    mx_printstr("========================================\n");
    //Path
    mx_printstr("Path: ");
    mx_printstr(islands[begin_index]);
    mx_printstr(" -> ");
    mx_printstr(islands[end_index]);
    mx_printchar('\n');
    //Route
    mx_printstr("Route: ");
    mx_printstr(islands[ver[k-1]-1]);
    for (int i = k - 2; i >= 0; i--){
        mx_printstr(" -> ");
        mx_printstr(islands[ver[i]-1]);
    }
    //Distance
    if(k == 2){
        mx_printstr("\nDistance: ");
        mx_printint(min_dist[end_index]);
    } else {
        mx_printstr("\nDistance: ");
        mx_printint(a[ver[k-1]-1][ver[k-2]-1]);
        for (int i = k - 2; i >= 1; i--){
            mx_printstr(" + ");
            mx_printint(a[ver[i]-1][ver[i-1]-1]);
        }
        mx_printstr(" = ");
        mx_printint(min_dist[end_index]);
    }
    mx_printstr("\n========================================\n");
    }
}

void parse_file(const char *file_name){
    char *str_all_file = mx_file_to_str(file_name);

    //First number
    if(str_all_file[0] == '\n'){
        mx_printerr("error: line 1 is not valid\n");
        exit(-1);
    }
    char *first_num_ch = mx_strndup(str_all_file, mx_get_char_index(str_all_file, '\n'));
    int first_num_int = -1;
    if(correct_digit(first_num_ch) ==  true) {
        first_num_int = mx_atoi(first_num_ch);
    } else {
        mx_printerr("error: line 1 is not valid\n");
        exit(-1);
    }

    //Split for a lines
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
        char *birdge_num = mx_strdup(&str_without_first_num[i][mx_get_char_index(str_without_first_num[i], ',')+1]);
        if(correct_line(from, to, birdge_num) == false) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i+2)); 
            mx_printerr(" is not valid\n");
            exit(-1);
        }
        sum_km += mx_atoi(birdge_num);
    }
    
    //Delete dublicate
    islands = without_dublicat(islands, count_lines, first_num_int);

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

    //Fill matrix
    for(int i = 0; str_without_first_num[i]; i++) {
        char *from = mx_strndup(str_without_first_num[i], mx_get_char_index(str_without_first_num[i], '-'));
        char *to = mx_strndup(&str_without_first_num[i][mx_get_char_index(str_without_first_num[i], '-')+1], mx_get_char_index(str_without_first_num[i], ',') - mx_strlen(from) - 1);
        char *birdge_num = mx_strdup(&str_without_first_num[i][mx_get_char_index(str_without_first_num[i], ',')+1]);
        int first_index = get_index_in_strarr(islands, from);
        int second_index = get_index_in_strarr(islands, to);
        if(matrix[first_index][second_index] == 0 && matrix[second_index][first_index] == 0){
        matrix[first_index][second_index] = mx_atoi(birdge_num);
        matrix[second_index][first_index] = mx_atoi(birdge_num);
        } else {
            mx_printerr("error: duplicate bridges\n");
            exit(-1);
        }
    }

    //Check for too long distance
    if(sum_km > 2147483647){
        mx_printerr("error: sum of bridges lengths is too big\n");
        exit(-1);
    }

    for(int i = 0; i < first_num_int; i++){
        printf("%s\t", islands[i]);
       for(int j = 0; j < first_num_int; j++){
        printf("%d\t", matrix[i][j]);
        }
        printf("%s", "\n");
    }
    printf("%s", "\n\n\n");
    for(int i = 0; i < first_num_int; i++){
        find_path(islands, matrix, i, first_num_int);
    }
}

int main(int argc, char *argv[]){
    if(argc != 2){
        mx_printerr("usage: ./pathfinder [filename]\n");
        exit(-1);
    }
    parse_file(argv[1]);
}
