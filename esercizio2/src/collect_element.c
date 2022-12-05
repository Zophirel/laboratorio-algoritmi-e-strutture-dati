#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "edit_distance.h"

//Struct to collect words of a given textfile
struct _WordsCollection{
    char **words;
    unsigned long size;
    unsigned long capacity;
};

unsigned long dynamicSize = 20;

void collection_free(Words *collection){
    for(unsigned long i = 0; i < collection -> size; i++){
        free(collection -> words[i]);
        collection -> words[i] = NULL;
    }
    free(collection -> words);
    collection -> words = NULL;
    free(collection);
    collection = NULL;
}

Words *collection_init(unsigned long size){
    Words *collection = malloc(sizeof(Words));
    collection -> words = malloc(size * sizeof(char *));
    if(collection == NULL || collection -> words == NULL){
        fprintf(stderr, "Unable to allocate memory for collection\n");
        collection_free(collection);
    }
    collection -> size = 0;
    collection -> capacity = size;
    return collection;
}

Words *collection_realloc(Words *collection, unsigned long size){
    collection -> words = realloc(collection -> words, size * sizeof(char *));
    if(collection -> words == NULL){
        fprintf(stderr, "Unable to reallocate memory for collection\n");
        collection_free(collection);
    }
    collection -> capacity = size;
    return collection;
}

void collection_insert(Words *collection, char *word){
    collection -> words[collection -> size] = word;
    collection -> size++;
}

void collection_show(Words *collection){
    for(unsigned long i = 0; i < collection -> size; i++)    
        printf("%s, len: %ld\n", collection -> words[i], strlen(collection -> words[i]));
}


//this function extract words from phrases with punctuation marks and white space 
//and put the extracted words in to a char pointer array
Words *collect_phrases(char *path){
    Words *collection = NULL;
    collection = collection_init(20);
    
    FILE *fp = fopen(path, "r");
    if(fp == NULL){
        fprintf(stderr, "correctme not found\n");
        collection_free(collection);
        exit(EXIT_FAILURE);
    }
    
    char buffer[20];
    char ch;
    
    int i = 0;
    while((ch = fgetc(fp)) != EOF){
        if(!isspace(ch)){
            if(!ispunct(ch)){   
                buffer[i] = ch;
                i++;
            }
        }else{
            buffer[i] = '\0';
            if(collection -> size == dynamicSize-1){
                dynamicSize *= 2;
                collection = collection_realloc(collection, dynamicSize);
            }
            collection_insert(collection, strdup(buffer));
            memset(buffer, 0, 20);
            i = 0;
        }
    }

    if(buffer[0] != 0){
        buffer[i] = '\0';
        if(collection -> size == dynamicSize-1){
            dynamicSize *= 2;
            collection = collection_realloc(collection, dynamicSize);
        }
        collection_insert(collection, strdup(buffer));
        memset(buffer, 0, 20);
    }

    fclose(fp);
    return collection;
}

//this function extract words from a list where each words are separated with an \n
Words *collection_dictionary(char *path){
    dynamicSize = 100;
    Words *collection = NULL;
    collection = collection_init(dynamicSize);
    
    FILE *fp = fopen(path, "r");
    if(fp == NULL){
        fprintf(stderr, "dictionary not found\n");
        collection_free(collection);
        exit(EXIT_FAILURE);
    }
    
    char buffer[100];
    char *line, *curr_word;
    unsigned long i = 0;
    while (fgets(buffer, 100, fp) && buffer[0] != '\n'){
        if(i == dynamicSize-1){
            dynamicSize *= 2;
            collection_realloc(collection, dynamicSize);
        }
        line = strdup(buffer);
        curr_word = strtok(line, "\n");
        collection_insert(collection, strdup(curr_word));
        i++;
        free(line);
    }
    fclose(fp);
    return collection;
}