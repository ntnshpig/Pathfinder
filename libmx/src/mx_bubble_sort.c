#include "../inc/libmx.h"

int mx_bubble_sort(char **arr, int size) {
    int count = 0;
    for (int i = 0; i < size-1; i++) {
        for (int z = 0; z < size-1; z++) {
            if (mx_strcmp(arr[z], arr[z+1]) > 0) {
                char *temp = arr[z];
                arr[z] = arr[z + 1];
                arr[z+1] = temp;
                count++;
            }
        }
    }
    return count;
}
