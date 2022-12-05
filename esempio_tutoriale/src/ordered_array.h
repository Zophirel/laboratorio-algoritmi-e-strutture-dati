#ifndef ORDERED_ARRAY_H
#define ORDERED_ARRAY_H

typedef struct _OrderedArray OrderedArray;

OrderedArray *ordered_array_create(int (*precedes) (void*,void*));
int ordered_array_is_empty(OrderedArray*);

unsigned long ordered_array_size(OrderedArray*);

void ordered_array_add(OrderedArray*,void*);

void *ordered_array_get(OrderedArray*,unsigned long);

void ordered_array_free_memory(OrderedArray*);


#endif
