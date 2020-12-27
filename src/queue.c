#include "../inc/pathfinder.h"

t_queue* new_node_qu(t_node *node) { 
    t_queue* new_node = (t_queue*)malloc(sizeof(t_queue)); 
    new_node->priority = node->all_way;
    new_node->next = NULL;
    new_node->node = node;
    return new_node; 
} 

void pop_front(t_queue** head) {//Delete 1 el
    t_queue* temp = *head; 
    (*head) = (*head)->next; 
    free(temp); 
} 

void push_to_qu(t_queue** head, t_node *node) { //Enter the el for priority
    t_queue* start = (*head); 
    t_queue* temp_node = new_node_qu(node); 
    if((*head) == NULL) {
        (*head) = temp_node;
        return;
    }    
    if ((*head)->priority > node->all_way) {         
        temp_node->next = *head; 
        (*head) = temp_node; 
    } else { 
        while (start->next != NULL && start->next->priority < node->all_way)
            start = start->next; 
        temp_node->next = start->next; 
        start->next = temp_node; 
    }
} 

int is_empty(t_queue** queue) { //Queue is empty
    if((*queue) == NULL) return 1; 
    else return 0;
} 
