#include "../inc/libmx.h"

void mx_pop_back(t_list **head) {
    if (head == NULL || *head == NULL) return;
    if((*head)->next == NULL) {
        free(*head);
        *head= NULL;
        return;
    }
    t_list *temp = *head;
    while (temp -> next -> next != NULL) 
        temp = temp -> next;
    free(temp -> next);
    temp -> next = NULL;
}
