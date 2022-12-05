#ifndef EDIT_DISTANCE_H
#define EDIT_DISTANCE_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _WordsCollection Words;
typedef struct Word wordlist;

void collection_free(Words *collection);
Words *collection_init(unsigned long size);
Words *collection_realloc(Words *collection, unsigned long size);
void collection_insert(Words *collection, char *word);
void collection_show(Words *collection);
Words *collect_phrases(char *path);
Words *collection_dictionary(char *path);
void collection_edit_distance(Words *correctme, Words *dictionary);
long unsigned int recursive_edit_distance(char* word1, char* word2);
int dynamic_edit_distance(char * str1, char * str2, int first_len, int second_len, int **rec_matrix);

int **create_matrix(char *w1, char *w2);
void free_matrix(int **matrix, char *w1);
int **init_matrix(char * word1, char * word2, int **matrix);
void show_matrix(int **m, char *w1, char *w2);
#endif 
