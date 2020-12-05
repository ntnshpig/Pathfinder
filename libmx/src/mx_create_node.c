#include "../inc/libmx.h"

t_list *mx_create_node(void *data) {
    if (!data) return NULL;
    t_list *new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node) return NULL;
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}
