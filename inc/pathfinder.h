#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "libmx.h"

//////Graph
typedef struct s_node {
    char *name;
    int all_way;
    struct s_node* parent; 
  
} t_node; 
t_node *new_node_gr(int all_way, char *name);
void push_node_qr(int all_way, char *name, t_node* parent);
//////Graph

///////Queue with priority
typedef struct s_queue {
    int priority; 
    t_node *node;
    struct s_queue* next; 
  
} t_queue; 
t_queue* new_node_qu(t_node* graph);
int is_empty(t_queue** queue);
void push_to_qu(t_queue** head, t_node* graph);
void pop_front(t_queue** head);
///////Queue with priority

/////Algorithm
t_node **generate_successors(int **matrix, t_node* parent, char **islands, int size);
t_node **pathfinder_alg(int **arr, char **islands, int cur_x, int goal_x, int size);
/////Algorithm

/////Sort
void sort_path_all(char **path, char **islands, int **arr, unsigned long size);
void sort_path_names(char **path, char **islands, unsigned long size);
int amount_of_num(int num);
int amount_of_el(char **arr);
/////Sort

////Checks
bool correct_digit(const char *num);
bool correct_word(const char *word);
bool correct_line(const char *from, const char *to, const char *bridge);
void check_extra_enter(char *str);
////Checks

int get_index_in_strarr(char **arr, char *sub);

char **without_duplicate(char **arr, int lines, int dif_isl);

void parse_file(const char *file_name);

void print_path(char *path, int **matrix, char **islands);

void way_to_str(t_node **res_paths, char **path, int size_path);
#endif
