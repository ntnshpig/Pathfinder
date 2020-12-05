#include "../inc/libmx.h"

void mx_push_back(t_list **list, void *data) {
    if(!data) return;
    if (!*list) {
        *list = mx_create_node(data);
    } else {
    t_list *last = *list;
    while (last -> next) 
        last = last -> next;
    last -> next = mx_create_node(data);
    }
}
