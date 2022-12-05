#include <stdio.h>
#include <stdlib.h>
typedef struct _OrderedArray OrderedArray;

int string_compare(void *, void *);
int int_compare(void *, void *);
int double_compare(void *, void *);

int tot_col(char *temp);
OrderedArray *ordered_array_init(int (*precedes)(void*, void*), unsigned long initialSize);
void ordered_array_realloc(OrderedArray *ordered_array, unsigned long int size);
void ordered_array_free(OrderedArray *ordered_array);
void check_mem(OrderedArray *rowArr, void **array, int sel);
void array_fill(OrderedArray *rowArr, void *r_record, void *r_cmp_col);
OrderedArray *ordered_array_load_csv(OrderedArray *arr, FILE * fp, int col);
void ordered_array_show(OrderedArray *);
void ordered_array_save(OrderedArray *);

void *get_the_value(void *);
void ordered_array_merge_sort(OrderedArray *ordered_array, void **temp, unsigned long low, unsigned long high);
void ordered_array_merge(OrderedArray *ordered_array, void **temp, unsigned long low, unsigned long mid, unsigned long high);
void swap(void **, void *, void *);
unsigned long find_position(OrderedArray *, void **, unsigned long, unsigned long, void *);
void binary_insertion_sort(OrderedArray *ordered_array, long unsigned int low, long unsigned int high);
void merge_binary_insertion_sort(OrderedArray *arr, unsigned long subseq, int order, int save);


void set_up_sort(char const *path, int (*precedes)(void*, void*));
