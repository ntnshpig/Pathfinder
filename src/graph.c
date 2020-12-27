#include "../inc/pathfinder.h"

t_node *new_node_gr(int all_way, char *name) { //Create node
    t_node* new_node = (t_node*)malloc(sizeof(t_node)); 
    new_node->name = mx_strdup(name);
    new_node->parent = NULL; 
    new_node->all_way = all_way; 
    return new_node; 
} 

void push_node_gr(int all_way, char *name, t_node* parent) { //Push node
    t_node* temp = new_node_gr(all_way, name);
    temp->parent = parent;
    parent = temp;
}
