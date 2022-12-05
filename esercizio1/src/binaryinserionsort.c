#include <string.h>
#include <limits.h>
#include "ordered_array.h"

struct _OrderedArray{
    void **record;
    void **cmp_col;
    unsigned long size;
    unsigned long capacity;
    int (*precedes) (void*, void*);
};

//binary serach the postion where "element" should be inserted into the "array", then i use that position to insert the record that
//contains "element" into the right position of ordered_array -> record[]
long unsigned int find_position(OrderedArray *ordered_array, void **array, long unsigned int low, long unsigned int high, void *element){
    long unsigned int mid = low + (high - low) / 2;    
    if(high - low == 0 || high - low == 1){   
        if(ordered_array -> precedes(array[mid], element)){
            if(ordered_array -> precedes(element, array[mid+1])){
                return mid+1;
            }
        }
        if(ordered_array -> precedes(element, array[mid]))
            return mid;

        if(ordered_array -> precedes(array[mid+1], element))
            return mid+2;
    }
    else{
        if(ordered_array -> precedes(element, array[mid]))
            return find_position(ordered_array, array, low, mid, element);
        else
            return find_position(ordered_array, array, mid, high, element);
    }
    
    return LONG_MAX; 
}


//it swap two elemnt of an array 
void swap(void **array, void *el0, void *el1){
    void *temp = el1;
    array[1] = el0;
    array[0] = temp;
}

void binary_insertion_sort(OrderedArray *ordered_array, long unsigned int low, long unsigned int high){  
    void *element;
    void *record;
    long unsigned int l = low; 
    
    for(low = low + 1; low < high; low++){     
        record = ordered_array -> record[low];
        element = ordered_array -> cmp_col[low];;
        long unsigned int index = find_position(ordered_array, ordered_array -> cmp_col, l, low, element);

        if(index == LONG_MAX){
            fprintf(stderr, "errore nella ricerca\n");
            exit(EXIT_FAILURE);
        }
       
        long unsigned int tmp = low;
        while(tmp > index){
            ordered_array -> record[tmp] = ordered_array -> record[tmp-1];
            ordered_array -> cmp_col[tmp] = ordered_array-> cmp_col[tmp-1];
            tmp--;
        }

        ordered_array -> record[index] = record;
        ordered_array -> cmp_col[index] = element;
    } 
}