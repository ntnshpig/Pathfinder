#include "../inc/pathfinder.h"

void find_path(char **islands, int **a, int begin_index, int size) {
    int min_dist[size]; //minimal distance
    int visited_node[size]; //visited vertex(only 0 and 1)
    int temp, minindex, min;
    
    //Initialization
    for (int i = 0; i<size; i++) {
        min_dist[i] = 2147483647;
        visited_node[i] = 1;
    }
    min_dist[begin_index] = 0;
    
    //Algorothm step
    do {
        minindex = 2147483647;
        min = 2147483647;
        for (int i = 0; i<size; i++) { // If the vertex is don`t visited 
            if ((visited_node[i] == 1) && (min_dist[i]<min)) {//and the weight is less than min
                min = min_dist[i];
                minindex = i;
            }
        }
        //Add new weight to the current
        //and compare it with minimal weight
        if (minindex != 2147483647) {
        for (int i = 0; i<size; i++) {
            if (a[minindex][i] > 0) {
                temp = min + a[minindex][i];
                if (temp < min_dist[i]) {
                    min_dist[i] = temp;
                }
            }
        }
        visited_node[minindex] = 0;
        }
    } while (minindex < 2147483647);
    
    //Making path from begin_index to every vertex
    for(int i = begin_index; i < size; i++) {
        int end = i;
        int end_index = end;
        if(min_dist[end_index] == 0 || min_dist[end_index] == 2147483647) continue;
        int vis_ver[size]; //visited vertex
        vis_ver[0] = end + 1;
        int k = 1; //Number of nodes among A and B
        int weight = min_dist[end];
        while (end != begin_index) {
            for (int i = 0; i<size; i++) { //Look all nodes
                if (a[i][end] != 0)  { //If we have bridge
                    int temp = weight - a[i][end]; //All ways from prev vertex
                    if (temp == min_dist[i]) {//If it right we came from this vertex
                        weight = temp;
                        end = i;//Previous vertex
                        vis_ver[k] = i + 1;
                        k++;
                    }
                }
            }
        }

        //Path output
        mx_printstr("========================================\n");
        //Path
        mx_printstr("Path: ");
        mx_printstr(islands[begin_index]);
        mx_printstr(" -> ");
        mx_printstr(islands[end_index]);
        mx_printchar('\n');
        
        //Route
        mx_printstr("Route: ");
        for (int i = k - 1; i >= 0; i--){
            mx_printstr(islands[vis_ver[i]-1]);
            if(i >= 1) mx_printstr(" -> ");
        }

        //Distance
        if(k == 2){
            mx_printstr("\nDistance: ");
            mx_printint(min_dist[end_index]);
            mx_printstr("\n========================================\n");
        } else {
            mx_printstr("\nDistance: ");
            mx_printint(a[vis_ver[k-1]-1][vis_ver[k-2]-1]);
            for (int i = k - 2; i >= 1; i--){
                mx_printstr(" + ");
                mx_printint(a[vis_ver[i]-1][vis_ver[i-1]-1]);
            }
            mx_printstr(" = ");
            mx_printint(min_dist[end_index]);
            mx_printstr("\n========================================\n");
        }
        //Find other ways
        if(k>2){
            int count_node = k-1;
            int **cpy_matrix = (int **)malloc((size*size)*sizeof(int));
            for(int i = 0; i < size; i++){
                cpy_matrix[i] = (int*)malloc((size) * sizeof(int));
            }
            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    cpy_matrix[i][j] = a[i][j];
                }
            }
            cpy_matrix[vis_ver[count_node-1]-1][vis_ver[count_node-2]-1] = 0;
            cpy_matrix[vis_ver[count_node-2]-1][vis_ver[count_node-1]-1] = 0;
            //Looking for other path without 1 connection
            while(count_node != -1){
            count_node = other_path(islands, cpy_matrix, begin_index, size, min_dist[end_index], end_index);
            }
        }
    }
}

int other_path(char **islands, int **matrix, int begin_index, int size, int res, int end)  {
    int min_dist[size];
    int visited_node[size];
    int temp, minindex, min;
    //Initialization
    for (int i = 0; i<size; i++) {
        min_dist[i] = 2147483647;
        visited_node[i] = 1;
    }
    min_dist[begin_index] = 0;
    //Algorithm step
    do { 
        minindex = 2147483647;
        min = 2147483647;
        for (int i = 0; i<size; i++) {
            if ((visited_node[i] == 1) && (min_dist[i]<min)) {
                min = min_dist[i];
                minindex = i;
            }
        }

        if (minindex != 2147483647) {
        for (int i = 0; i<size; i++) {
            if (matrix[minindex][i] > 0) {
                temp = min + matrix[minindex][i];
                if (temp < min_dist[i]) {
                    min_dist[i] = temp;
                }
            }
        }
        visited_node[minindex] = 0;
        }
    } while (minindex < 2147483647);

    //Build a path
    int end_index = end;
    if(min_dist[end_index] == 0 || min_dist[end_index] == 2147483647) return -1;
    int vis_ver[size];
    vis_ver[0] = end + 1;
    int k = 1;
    int weight = min_dist[end];
    int dop[size];
    dop[0] = end + 1;
    while (end != begin_index) {
        for (int i = 0; i<size; i++) {
            if (matrix[i][end] != 0)  {
                int temp = weight - matrix[i][end];
                if (temp == min_dist[i]) {
                    weight = temp;
                    end = i;
                    vis_ver[k] = i + 1;
                    k++;
                }
            }
        }
    }

    //Output the path
    if(min_dist[end_index] == res) {
        mx_printstr("========================================\n");
        //Path
        mx_printstr("Path: ");
        mx_printstr(islands[begin_index]);
        mx_printstr(" -> ");
        mx_printstr(islands[end_index]);
        mx_printchar('\n');
        //Route
        mx_printstr("Route: ");
        for (int i = k - 1; i >= 0; i--){
            mx_printstr(islands[vis_ver[i]-1]);
            if(i >= 1) mx_printstr(" -> ");
        }
        //Distance
        if(k == 2){
            mx_printstr("\nDistance: ");
            mx_printint(min_dist[end_index]);
        } else {
            mx_printstr("\nDistance: ");
            mx_printint(matrix[vis_ver[k-1]-1][vis_ver[k-2]-1]);
            for (int i = k - 2; i >= 1; i--){
                mx_printstr(" + ");
                mx_printint(matrix[vis_ver[i]-1][vis_ver[i-1]-1]);
            }
            mx_printstr(" = ");
            mx_printint(min_dist[end_index]);
        }
        mx_printstr("\n========================================\n");
        }
    //Delete last connection
    matrix[vis_ver[k-1]-1][vis_ver[k-2]-1] = 0;
    matrix[vis_ver[k-2]-1][vis_ver[k-1]-1] = 0;
    return k;
}
