#include "../inc/libmx.h"

void mx_pop_front(t_list **head) {
    if(*head == NULL || head == NULL) return;
    if((*head)->next == NULL) {
        free(*head);
        (*head) = NULL;
    } else {
   	t_list *node = (*head)->next;
    free(*head);
    (*head) =  NULL;
    *head = node;
    }
}
