#include "../inc/pathfinder.h"

t_node **generate_successors(int **matrix, t_node* parent, char **islands, int size) {
    int index = 0;

    while(mx_strcmp(islands[index], parent->name) != 0) index++;

    t_node **successors = (t_node **) malloc((size) * sizeof(t_node *));
    for(int i = 0; i < size; i++) {
        successors[i] = (t_node*)malloc(sizeof(t_node));
        successors[i] = NULL;
    }

    for(int i = 0; i < size; i++) {
        if(i != index && matrix[index][i] != -1 && parent != NULL) {        
            t_node *temp = parent;
            bool was = false;
            int j = 0;
            while(temp != NULL) {
                if(mx_strcmp(temp->name, islands[i]) == 0 || j > size) {
                    was = true;
                    break;
                }
                temp = temp->parent;  
                j++;              
            }
            if(j > size) break;
            if (was == false)
                successors[i] = new_node_gr(parent->all_way + matrix[index][i], islands[i]);
        }
    }

    int lenght = 0;
    for(int i = 0; i < size; i++) {
        if(successors[i] != NULL) lenght++;
    }

    t_node **successors_res = (t_node **) malloc((lenght + 1) * sizeof(t_node *));
    for(int i = 0; i < lenght + 1; i++)
        successors_res[i] = NULL;

    lenght = 0;
    for(int i = 0; i < size; i++) {
        if(successors[i] != NULL) {
            successors_res[lenght] = (t_node *) malloc(sizeof(t_node ));
            successors_res[lenght] = successors[i];
            lenght++;
        }
    }

    return successors_res;
}

t_node **pathfinder_alg(int **arr, char **islands, int cur_x, int goal_x, int size) {
    t_node *way = new_node_gr(0, islands[cur_x]);
    t_queue *queue = new_node_qu(way);
    t_queue *queue_close = new_node_qu(way);

    t_node **paths = (t_node **)malloc(mx_pow(size, 2) * sizeof(t_node *));
    for(int i = 0; i < size; i++) {
        paths[i] = (t_node*)malloc(sizeof(t_node));
        paths[i] = NULL;
    }
    int paths_index = 0;
    int check = 0;

    while (!is_empty(&queue)) {
        check++;
        way = queue->node;
        pop_front(&queue);

        t_node *temp = way;
        int j = 0;
        for(; temp->parent != NULL; j++) {
            if(j > size)
                break;
            temp = temp->parent;
        }
        if(j >= size) continue;

        bool in_islands = false;
        for(int h = 0; h < size; h++) {
            if(mx_strcmp(way->name, islands[h]) == 0) {
                in_islands = true;
            }
        }
        if(in_islands == false) continue;
        
        t_node **successors = generate_successors(arr, way, islands, size);  

        for (int i = 0; successors[i] != NULL; i++)
            successors[i]->parent = way;

        for (int i = 0; successors[i] != NULL; i++) {
            if(mx_strcmp(successors[i]->name, islands[goal_x]) == 0) {
                paths[paths_index] = successors[i];
                paths_index++;
            }

            t_queue *temp_queue = queue;
            bool in_queue = false;
            while(temp_queue != NULL) {
                if(mx_strcmp(temp_queue->node->name, successors[i]->name) == 0) {
                    if(temp_queue->node->all_way < successors[i]->all_way) {
                        in_queue = true;
                        break;
                    }
                }
                temp_queue = temp_queue->next;
            }

            bool in_cose_queue = false;
            t_queue *queue_close_temp = queue_close;
            while(queue_close_temp != NULL) {
                if(mx_strcmp(queue_close_temp->node->name, successors[i]->name) == 0) {
                    if(queue_close_temp->node->all_way < successors[i]->all_way) {
                        in_cose_queue = true;
                        break;
                    }
                }
                queue_close_temp = queue_close_temp->next;
            }

            
            if(in_queue == false && in_cose_queue == false) {
                push_to_qu(&queue, successors[i]);
                push_to_qu(&queue_close, successors[i]);
            }  
        }
    }
    return paths;
}
