#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "unity.h"
#include "edit_distance.h"

struct _WordsCollection{
    char **words;
    unsigned long size;
    unsigned long capacity;
};

struct Word{
    char *elem;
    int  dist;
    
    struct MinEditWords{
        char **arr;
        unsigned long size;
    } *edit_word_list;
};

void coll_free(Words *collection){
    free(collection -> words);
    collection -> words = NULL;
    free(collection);
    collection = NULL;
}

static void test_collection_is_initialized_correctly(){
    Words *test_collection = collection_init(100);
    TEST_ASSERT_EQUAL_INT(0, test_collection -> size);
    TEST_ASSERT_EQUAL_INT(100, test_collection -> capacity);
    TEST_ASSERT_NOT_NULL(test_collection -> words);
    coll_free(test_collection);
}

static void test_collection_insert(){
    Words *test_collection = collection_init(1);
    collection_insert(test_collection, "abc");
    TEST_ASSERT_EQUAL_STRING("abc", test_collection -> words[0]);
    coll_free(test_collection);
}

static void test_collection_realloc(){
    Words *test_collection = collection_init(1);
    collection_insert(test_collection, "abc");
    collection_realloc(test_collection, 2);
    collection_insert(test_collection, "bcd");
    TEST_ASSERT_EQUAL_STRING("bcd", test_collection -> words[1]);
    coll_free(test_collection);
}

static void test_collect_phrases(){
    FILE *fp = fopen("test_file.txt", "w");
    fprintf(fp, "Hello, Word.");
    fclose(fp);
    
    Words *test_collection = collect_phrases("test_file.txt");    
    TEST_ASSERT_EQUAL_STRING("Hello", test_collection -> words[0]);
    remove("test_file.txt");
    collection_free(test_collection);
}

static void test_collect_dictionary(){
    FILE *fp = fopen("test_file.txt", "w");
    fprintf(fp, "Hello\nWord\n");
    fclose(fp);
    Words *test_collection = collection_dictionary("test_file.txt");
    TEST_ASSERT_EQUAL_STRING("Hello", test_collection -> words[0]);
    remove("test_file.txt");
    collection_free(test_collection);
}

static void test_collection_edit_distance(){
    FILE *dictionary = fopen("dic_test_file.txt", "w");
    fprintf(dictionary, "Hello\nWord\n");
    
    FILE *correctme = fopen("corr_test_file.txt", "w");
    fprintf(correctme, "rllo, Wo.");
    
    fclose(dictionary);
    fclose(correctme);
    
    Words *test_collection = collection_dictionary("dic_test_file.txt");
    Words *test_collection2 = collect_phrases("corr_test_file.txt");
    collection_edit_distance(test_collection2, test_collection);

    remove("dic_test_file.txt");
    remove("corr_test_file.txt");

    collection_free(test_collection);
    collection_free(test_collection2);
}

static void test_left_to_right_rec_edit_dist(){
    unsigned long edit_ins = recursive_edit_distance("ciao", "iao");
    unsigned long edit_del = recursive_edit_distance("iao", "ciao");
    unsigned long edit_replace = recursive_edit_distance("riao", "ciao");
    TEST_ASSERT_EQUAL_UINT(1, edit_ins);
    TEST_ASSERT_EQUAL_UINT(1, edit_del);
    TEST_ASSERT_EQUAL_UINT(2, edit_replace);
}

static void test_left_to_right_rec_edit_dist_with_empty_words(){
    unsigned long zero = recursive_edit_distance("", "");
    TEST_ASSERT_EQUAL_UINT(0, zero);
}

static void test_left_to_right_edit_dist_with_oen_word(){
    unsigned long quattro = recursive_edit_distance("ciao", "");
    TEST_ASSERT_EQUAL_UINT(4, quattro);
}

static void test_matrix_init(){
    int **matrix = create_matrix("ciao", "ciao");
    init_matrix("ciao", "ciao", matrix);
    int len1 = (int)strlen("ciao");
    int len2 = len1;

    for(int i = 0; i <= len1; i++){
        for(int j = 0; j <= len2; j++){
            TEST_ASSERT_EQUAL_INT(-1, matrix[i][j]);
        }
    }

    free_matrix(matrix, "ciao");
}


static void test_dp_rec_edit_dist(){
    int **matrix = create_matrix("ciao", "iao");
    init_matrix("ciao", "iao", matrix);
    int edit_inst = dynamic_edit_distance("ciao", "iao", (int)strlen("ciao"), (int)strlen("iao"), matrix);
    free_matrix(matrix, "ciao");
    TEST_ASSERT_EQUAL_INT(1, edit_inst);

    matrix = create_matrix("iao", "ciao");
    init_matrix("iao", "ciao", matrix);
    int edit_del = dynamic_edit_distance("iao", "ciao", (int)strlen("iao"), (int)strlen("ciao"), matrix);
    free_matrix(matrix, "iao");
    TEST_ASSERT_EQUAL_INT(1, edit_del);

    matrix = create_matrix("riao", "ciao");
    init_matrix("riao", "ciao", matrix);
    int edit_repl = dynamic_edit_distance("riao", "ciao", (int)strlen("riao"), (int)strlen("ciao"), matrix);
    free_matrix(matrix, "riao");
    TEST_ASSERT_EQUAL_INT(2, edit_repl);
}

static void test_dp_rec_edit_dist_zero_el(){
    int **matrix = create_matrix("", "");
    init_matrix("", "", matrix);
    int edit_dist = dynamic_edit_distance("", "", (int)strlen(""), (int)strlen(""), matrix);
    free_matrix(matrix, "");
    TEST_ASSERT_EQUAL_INT(0, edit_dist);
}

static void test_dp_rec_edit_dist_one_el(){
    int **matrix = create_matrix("ciao", "");
    init_matrix("ciao", "", matrix);
    int edit_dist = dynamic_edit_distance("ciao", "", (int)strlen("ciao"), (int)strlen(""), matrix);
    free_matrix(matrix, "ciao");
    TEST_ASSERT_EQUAL_INT((int)strlen("ciao"), edit_dist);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_collection_is_initialized_correctly);
    RUN_TEST(test_collection_insert);
    RUN_TEST(test_collection_realloc);
    RUN_TEST(test_collect_phrases);
    RUN_TEST(test_collect_dictionary);
    RUN_TEST(test_collection_edit_distance);
    RUN_TEST(test_left_to_right_rec_edit_dist);
    RUN_TEST(test_left_to_right_rec_edit_dist_with_empty_words);
    RUN_TEST(test_left_to_right_edit_dist_with_oen_word);
    RUN_TEST(test_matrix_init);
    RUN_TEST(test_dp_rec_edit_dist);
    RUN_TEST(test_dp_rec_edit_dist_zero_el);
    RUN_TEST(test_dp_rec_edit_dist_one_el);
    return UNITY_END();
    
}