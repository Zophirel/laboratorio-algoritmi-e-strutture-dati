#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "unity.h"
#include "ordered_array.h"

struct _OrderedArray{
    void **record;
    void **cmp_col;
    unsigned long size;
    unsigned long capacity;
    int (*precedes) (void*, void*);
};

//i use this function to free the arrays in the test since no values is malloc'd 
//inside the array record and the array cmp_col
void ordered_array_free_pointers_only(OrderedArray *ordered_array){  
    free(ordered_array -> record);
    free(ordered_array -> cmp_col);
    free(ordered_array);
    ordered_array -> record = NULL;
    ordered_array -> cmp_col = NULL;
    ordered_array = NULL;
}

void test_if_array_is_initialized(){
    OrderedArray *arr = ordered_array_init((string_compare),100);
    TEST_ASSERT_EQUAL_UINT(100, arr -> capacity);
    TEST_ASSERT_EQUAL_UINT(0, arr -> size);
    TEST_ASSERT_EQUAL_INT((string_compare), arr -> precedes);
    ordered_array_free_pointers_only(arr);
}

static OrderedArray *unordered_array(){
    OrderedArray *arr = ordered_array_init(int_compare, 100);
    
    int x = 20;
    arr -> record[0] = &x;
    arr -> cmp_col[0] = &x;
    
    int y = 30;
    arr -> record[1] = &y;
    arr -> cmp_col[1] = &y;

    int z = 10;
    arr -> record[2] = &z;
    arr -> cmp_col[2] = &z;

    arr -> size = 3;
    
    return arr; 
}

static OrderedArray *same_array(){
    OrderedArray *arr = ordered_array_init(int_compare, 3);
    
    int x = 10;
    arr -> record[0] = &x;
    arr -> cmp_col[0] = &x;
    
    int y = 10;
    arr -> record[1] = &y;
    arr -> cmp_col[1] = &y;

    int z = 0;
    arr -> record[2] = &z;
    arr -> cmp_col[2] = &z;

    arr -> size = 3;
    
    return arr; 
}

void test_if_array_is_reallocated(){
    OrderedArray *arr = ordered_array_init(int_compare, 3);
    int x = 10;
    arr -> record[0] = &x;
    arr -> cmp_col[0] = &x;
    
    int y = 10;
    arr -> record[1] = &y;
    arr -> cmp_col[1] = &y;

    int z = 0;
    arr -> record[2] = &z;
    arr -> cmp_col[2] = &z;
    
    arr -> size = 3;

    ordered_array_realloc(arr, 6);
    
    int a = 40;
    arr -> record[3] = &a;
    arr -> cmp_col[3] = &a;

    int b = 50;
    arr -> record[4] = &b;
    arr -> cmp_col[4] = &b;

    arr -> size = 5;

    TEST_ASSERT_EQUAL_INT(50, *(int *)arr -> record[4]);

    ordered_array_free_pointers_only(arr);
    
}

static OrderedArray *empty_array(){
    OrderedArray *arr = ordered_array_init(int_compare, 100);    
    return arr; 
}

static void test_ordered_array_accept_int(){
    OrderedArray * arr = ordered_array_init(int_compare, 100);
    
    int x = 10;
    arr -> record[0] = &x;
    
    TEST_ASSERT_EQUAL_INT(10, *(int*)arr -> record[0]);
    ordered_array_free(arr);

}

static void test_ordered_array_accept_float(){
    OrderedArray * arr = ordered_array_init(double_compare, 100);
    double value = 10.327;
    float x = (float)value;
    arr -> record[0] = &x;
    
    TEST_ASSERT_EQUAL_FLOAT(10.327, *(float*)arr -> record[0]);
    ordered_array_free(arr);

}

static void test_ordered_array_accept_string(){
    OrderedArray * arr = ordered_array_init(string_compare, 100);
    char *a = "string\0";
    arr -> record[0] = a;
    
    TEST_ASSERT_EQUAL_STRING("string", arr -> record[0]);
    ordered_array_free(arr);
}

static void test_binaryinsertionsort(){
    OrderedArray * arr = unordered_array();
    binary_insertion_sort(arr, 0, arr->size);
    
    TEST_ASSERT_EQUAL_INT(10, *(int *)arr -> record[0]);
    ordered_array_free_pointers_only(arr);
}

static void test_binaryinsertionsort_with_equal_values(){
    OrderedArray * arr = same_array();
    binary_insertion_sort(arr, 0, arr->size);
    TEST_ASSERT_EQUAL_INT(10, *(int *)arr -> record[1]);
    TEST_ASSERT_EQUAL_INT(10, *(int *)arr -> record[2]);
    ordered_array_free_pointers_only(arr);
}

//test for the empty array to see if the process crash
static void test_binaryinsertionsort_empty_arr(){
    OrderedArray * arr = empty_array();
    binary_insertion_sort(arr, 0, arr->size);
    ordered_array_free_pointers_only(arr);
}

static void test_csv_loader(){
    OrderedArray * arr = ordered_array_init((int_compare), 3);
    FILE *fp = fopen("src/testfile.csv", "r");
    ordered_array_load_csv(arr, fp, 3);
    TEST_ASSERT_EQUAL_INT(123, *(int *)arr -> cmp_col[0]);    
    ordered_array_free(arr);
    fclose(fp);
}

static void test_mergebininssort(){
    OrderedArray * arr = ordered_array_init((int_compare), 3);
    FILE *fp = fopen("src/testfile.csv", "r");
    ordered_array_load_csv(arr, fp, 3);
    merge_binary_insertion_sort(arr, 2, 0, 0);
    TEST_ASSERT_EQUAL_STRING("2, abc, 000, 123.321", (char *)arr -> record[0]);
    ordered_array_free(arr);
}

static void test_mergesort(){
    OrderedArray * arr = ordered_array_init((int_compare), 3);
    FILE *fp = fopen("src/testfile.csv", "r");
    ordered_array_load_csv(arr, fp, 3);
    void *temp = malloc(arr -> size * sizeof(void *));
    ordered_array_merge_sort(arr, temp, 0, arr -> size);
    TEST_ASSERT_EQUAL_STRING("2, abc, 000, 123.321", (char *)arr -> record[0]);
    ordered_array_free_pointers_only(arr);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_if_array_is_initialized);
    RUN_TEST(test_if_array_is_reallocated);
    RUN_TEST(test_ordered_array_accept_int);
    RUN_TEST(test_ordered_array_accept_float);   
    RUN_TEST(test_ordered_array_accept_string);
    RUN_TEST(test_binaryinsertionsort);
    RUN_TEST(test_binaryinsertionsort_empty_arr);
    RUN_TEST(test_binaryinsertionsort_with_equal_values);
    RUN_TEST(test_csv_loader);
    RUN_TEST(test_mergebininssort);
    RUN_TEST(test_mergesort);
    
    return UNITY_END();
    
}
