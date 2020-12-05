#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "libmx.h"
#include "limits.h"

typedef struct s_graph {
    size_t sum;
    size_t size;
    bool **visited;
    char **vertices;
    size_t **dependences;
} t_graph;

t_graph *mx_create_graph(size_t);
void mx_delete_graph(t_graph **);
void mx_push_vertex(t_graph **, const char *);
void mx_set_dependences(t_graph **, const char*, const char *, const char *);
void mx_dijkstra(t_graph **, const char *);
int mx_get_vertex_index(t_graph *, const char *);
size_t mx_get_last_vertex_index(t_graph *);
bool mx_check_isduplicate(t_graph *, const char *, const char *);
bool mx_isvalid(const char *, const char *, const char *);
bool mx_check_if_sum_is_too_big(t_graph *);

#endif
