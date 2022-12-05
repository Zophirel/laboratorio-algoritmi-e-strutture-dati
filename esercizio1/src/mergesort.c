#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "ordered_array.h"

struct _OrderedArray{
    void **record;
    void **cmp_col;
    unsigned long size;
    unsigned long capacity;
    int (*precedes) (void*, void*);
};

void ordered_array_merge(OrderedArray *ordered_array, void **temp, unsigned long low, unsigned long mid, unsigned long high){
    unsigned long i, j, k = 0;
    void **element = ordered_array -> cmp_col;
    void **record  = ordered_array -> record;
    i = low;
    j = mid + 1;
    
    while (i <= mid && j <= high && element[i] && element[j] && record[i] && record[j]) {
        void *dup1 = strdup(record[i]);
        void *dup2 = strdup(record[j]);
        void *a = get_the_value(dup1);
        void *b = get_the_value(dup2);
        
        if (ordered_array -> precedes(a, b)) {
            temp[k] = record[i];
            i++;
        } else {
            temp[k] = record[j];
            j++;
        }
        k++;
        free(dup1);
        free(dup2);
    }

    while (i <= mid) {
        temp[k] = record[i];
        i++;
        k++;
    }
    
    while (j <= high) {
        temp[k] = record[j];
        j++;
        k++;
    }
    
    for (k = low; k <= high; k++)
        record[k] = temp[k-low];

    return;
}

void ordered_array_merge_sort(OrderedArray *ordered_array, void **temp, unsigned long low, unsigned long high){   
    if (low < high) {
        unsigned long mid = low + (high - low) / 2;
        ordered_array_merge_sort(ordered_array,  temp, low, mid);
        ordered_array_merge_sort(ordered_array, temp, mid + 1, high);

        ordered_array_merge(ordered_array, temp, low, mid, high);
    }
    
}