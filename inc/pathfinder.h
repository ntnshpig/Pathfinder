#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "libmx.h"

bool correct_digit(const char *num);
bool correct_word(const char *word);
bool correct_line(const char *from, const char *to, const char *bridge);
void check_extra_enter(char *str);

int get_index_in_strarr(char **arr, char *sub);

char **without_duplicate(char **arr, int lines, int dif_isl);

void parse_file(const char *file_name);

void find_path(char **islands, int **a, int begin_index, int size);
int other_path(char **islands, int **a, int begin_index, int size, int res, int end);

#endif
