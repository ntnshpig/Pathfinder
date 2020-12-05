#include "../inc/libmx.h"

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)){
    int size  = mx_list_size(lst);
    if(!lst || !cmp) return NULL;
       for (int i = 0; i < size -1; i++){
            t_list *list = lst;
            while(list->next){
                if (cmp(list->data, list->next->data)) {
                    void *temp = list->data;
                    list->data = list->next->data;
                    list->next->data = temp;
                }
                list = list->next;
            }
       }
    return lst;
}
