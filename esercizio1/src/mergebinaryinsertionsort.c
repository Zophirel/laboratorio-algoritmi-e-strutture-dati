#include "ordered_array.h"
#include <time.h>

struct _OrderedArray{
    void **record;
    void **cmp_col;
    unsigned long size;
    unsigned long capacity;
    int (*precedes) (void*, void*);
};

void merge(OrderedArray *arr, OrderedArray *first, OrderedArray *second){
    unsigned long int i = 0, j = 0, k = 0;
    while (i < first->size && j < second->size) {
        if (arr -> precedes(first -> cmp_col[i], second ->cmp_col[j])) {
            arr->record[k] = first->record[i];
            arr->cmp_col[k] = first->cmp_col[i];
            i++;
        }
        else {
            arr->record[k] = second->record[j];
            arr->cmp_col[k] = second->cmp_col[j];
            j++;
        }
        k++; 
    }
    while (i < first->size) {
        arr->record[k] = first->record[i];
        arr->cmp_col[k] = first->cmp_col[i];
        i++;
        k++;
    }
    while (j < second->size) {
        arr->record[k] = second->record[j];
        arr->cmp_col[k] = second->cmp_col[j];
        j++;
        k++;
    }
}

void split(OrderedArray * arr, OrderedArray * temp, unsigned long low, unsigned long high){
    for(unsigned long int i = low; i < high; i++){
        array_fill(temp, arr -> record[i], arr -> cmp_col[i]);
    }
}

extern int ord;

void merge_binary_insertion_sort(OrderedArray *arr, unsigned long subseq, int order, int save){
    ord = order;  
    if(subseq > 1){    
        unsigned long first_size = arr -> size/2;
        OrderedArray *first = NULL;
        first =  ordered_array_init(arr -> precedes, first_size);
        
        unsigned long second_size = arr -> size - first_size;
        OrderedArray *second = ordered_array_init(arr -> precedes, second_size);

        split(arr, first, 0, first -> capacity);
        split(arr, second, first -> size, first -> size + second -> capacity);

        if(first -> size > subseq){
            merge_binary_insertion_sort(first, subseq, order, save);
        }else{
            binary_insertion_sort(first, 0, first -> size);
        }

        if(second -> size > subseq){
            merge_binary_insertion_sort(second, subseq, order, save);
        }else{
            binary_insertion_sort(second, 0, second -> size);
        }
        
        merge(arr, first, second);

        free(first -> cmp_col);
        free(first -> record);
        free(first);

        free(second -> cmp_col);
        free(second -> record);
        free(second);
    }else{
        void **mergetemparr = malloc(arr -> size * sizeof(void *));
        ordered_array_merge_sort(arr, mergetemparr, 0, arr -> size);  
        free(mergetemparr);
    }
    if(save == 1){
        ordered_array_save(arr);
    }
}