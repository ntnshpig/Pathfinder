#include "../inc/libmx.h"

void mx_push_front(t_list **list, void *data) {
	if(!data) return;
	if (!*list) {
        *list = mx_create_node(data);
    } 
	else {
	t_list *front = mx_create_node((int *)data);
	front->next = *list;
	*list = front;
	}
}
