#include "ordered_array.h"
#include <stdlib.h>
#include <stdio.h>
#define INITIAL_CAPACITY 1024

static unsigned long get_index_to_insert(OrderedArray *ordered_array, void *element);
static void insert_element(OrderedArray *ordered_array, void *element, unsigned long index);

struct _OrderedArray {
    
    void **array;
    unsigned long size;
    unsigned long array_capacity;
    int (*precedes) (void*,void*);
    
};

OrderedArray *ordered_array_create(int (*precedes) (void*,void*)){
    
    if( precedes==NULL){
        
        fprintf(stderr, "ordered_array_create: precedes parameter cannot be NULL");
        exit(EXIT_FAILURE);
        
    }
    
    OrderedArray *ordered_array = (OrderedArray*) malloc(sizeof(OrderedArray));
    
    if(ordered_array == NULL){
        
        fprintf(stderr, "ordered_array_create: unable to allocate memory for the ordered array");
        exit(EXIT_FAILURE);
        
    }
    
    ordered_array->array = (void**) malloc(INITIAL_CAPACITY * sizeof(void*));
    
    if(ordered_array->array == NULL){
        
        fprintf(stderr, "ordered_array_create: unable to allocate memory for the ordered array");
        exit(EXIT_FAILURE);
        
    }
    
    ordered_array->size = 0;
    ordered_array->array_capacity = INITIAL_CAPACITY;
    ordered_array->precedes = precedes;
    return ordered_array;
    
}

int ordered_array_is_empty(OrderedArray *ordered_array){
    
    if(ordered_array == NULL){
        
        fprintf(stderr, "ordered_array_is_empty: ordered_array parameter cannot be NULL");
        exit(EXIT_FAILURE);
        
    }
    
    return ordered_array->size == 0;
    
}

unsigned long ordered_array_size(OrderedArray *ordered_array){
    
    if(ordered_array == NULL){
        
        fprintf(stderr, "ordered_array_size: ordered_array parameter cannot be NULL");
        exit(EXIT_FAILURE);
        
    }
    
    return ordered_array->size;
    
}

static unsigned long get_index_to_insert(OrderedArray *ordered_array,void *element){
    
    unsigned long i = 0;
    
    while (i < ordered_array->size){
        
        if(ordered_array->precedes(element,ordered_array->array[i]))
            
            break;
        
        i++;
        
    }
    
    return i;
    
}

static void insert_element(OrderedArray *ordered_array,void *element, unsigned long index){
    
    for(unsigned long i = ordered_array->size;i > index; --i){
        
        ordered_array->array[i] = ordered_array->array[i-1];
        
    }
    
    ordered_array->array[index] = element;
    
}

void ordered_array_add(OrderedArray *ordered_array,void *element){
    
     if(ordered_array == NULL){
        
        fprintf(stderr, "ordered_array_add: ordered_array parameter cannot be NULL");
        exit(EXIT_FAILURE);
        
    }
    
     if(element == NULL){
        
        fprintf(stderr, "ordered_array_add: element parameter cannot be NULL");
        exit(EXIT_FAILURE);
        
    }
    
    if(ordered_array->size >= ordered_array->array_capacity) {
     
        ordered_array->array_capacity = 2 * ordered_array->array_capacity;
        
        ordered_array->array = (void**)realloc(ordered_array->array,ordered_array->array_capacity * sizeof(void*));
        
        if(ordered_array->array == NULL){
        
            fprintf(stderr, "ordered_array_add: unable to allocate memory to host the new element");
            exit(EXIT_FAILURE);
        
        }
        
    }
    
    unsigned long index = get_index_to_insert(ordered_array,element);
    insert_element(ordered_array,element,index);
    ordered_array->size++;
    
}

void *ordered_array_get(OrderedArray *ordered_array,unsigned long i){
    
    if(ordered_array == NULL){
        
        fprintf(stderr, "ordered_array_get: ordered_array parameter cannot be NULL");
        exit(EXIT_FAILURE);
        
    }
    
    if(i >= ordered_array->size){
        
        fprintf(stderr, "ordered_array_get: Index %lu is out of the array bounds", i);
        exit(EXIT_FAILURE);
        
    }
    
    return ordered_array->array[i];
    
}

void ordered_array_free_memory(OrderedArray *ordered_array){
    
   if(ordered_array == NULL){
        
        fprintf(stderr, "ordered_array_free_memory: ordered_array parameter cannot be NULL");
        exit(EXIT_FAILURE);
        
    }
    
    free(ordered_array->array);
    free(ordered_array);
    
}
