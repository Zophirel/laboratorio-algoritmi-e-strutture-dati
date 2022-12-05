#include <limits.h>
#include "edit_distance.h"

//words collection, it's a struct made to contain the words from
//"correctme.txt" and "dictionary" in a "list" form
struct _WordsCollection{
    char **words;
    unsigned long size;
    unsigned long capacity;
};

//struct Word (wordlist) is a struct made purely for calculating the edit distance of a word from "correctme.txt"
//with each word of "dictionary.txt" 
struct Word{
    char *elem;
    int  dist;
    
    //sub struct MinEditWords collect the "dictionary.txt" words that have minimum edit distance 
    struct MinEditWords{
        char **arr;
        unsigned long size;
    } *edit_word_list;
};

wordlist *create_wordlist(){
    wordlist *checked_word = malloc(sizeof(wordlist));
    checked_word -> edit_word_list = malloc(sizeof(struct MinEditWords));
    checked_word -> edit_word_list -> arr = malloc(sizeof(char *) * 10);
    checked_word -> edit_word_list -> size = 0;
    checked_word -> dist = INT_MAX;
    return checked_word;
}

void free_wordlist(wordlist *checked_word){
    free(checked_word -> edit_word_list -> arr);
    free(checked_word -> edit_word_list);
    free(checked_word);
}

//it just prints the result of collection_edit_distance in a formatted way
void print_list(FILE *fp, wordlist *checked_word){
    fprintf(fp, " \"%s\" ha edit distance %d con ", checked_word -> elem, checked_word -> dist);
    for(unsigned long i = 0; i < checked_word -> edit_word_list -> size; i++){
        if(checked_word -> edit_word_list -> size == 1)
            fprintf(fp, "[%s]", checked_word -> edit_word_list -> arr[i]);
        else if(i == 0)
            fprintf(fp, "[%s, ", checked_word -> edit_word_list -> arr[i]);
        else if(i < checked_word -> edit_word_list -> size-1)
            fprintf(fp, "%s, ", checked_word -> edit_word_list -> arr[i]);
        else
            fprintf(fp, "%s]", checked_word -> edit_word_list -> arr[i]);
    }
    fprintf(fp, "\n");
}

//this function calculate the return value of dynamic_edit_distance  
void collection_edit_distance(Words *correctme, Words *dictionary){
    
    //in the end all the word inside edit_word_list -> arr will be put
    //inside a file algon with the relative "correctme.txt" word
    FILE *fp;
    fp = fopen("edit_list.txt", "w");
    int **edit_table = NULL;
    wordlist *checked_word;
    char *w1, *w2;
    unsigned long arr_size = 10;

    //of each word of "correctme.txt"
    for(unsigned long i = 0; i < correctme -> size; i++){
        checked_word = create_wordlist();
        w1 = correctme -> words[i];
        checked_word -> elem = w1;
        int w1_len = (int)strlen(w1);

        //with each of "dictionary.txt" 
        for(unsigned long j = 0; j < dictionary -> size; j++){
            w2 = dictionary -> words[j];
            edit_table = create_matrix(w1, w2);
            init_matrix(w1, w2, edit_table);

            int edit_dist = dynamic_edit_distance(w1, w2,  w1_len, (int)strlen(w2), edit_table);
            
            //if the two word calculated have the same edit_dist encountered until now
            //then we just insert the current "dictionary.txt" word inside the edit_word_list -> arr
            if(checked_word -> dist == edit_dist){
                if(checked_word -> edit_word_list -> size < arr_size){
                    checked_word -> edit_word_list -> arr[checked_word -> edit_word_list -> size] = w2;
                    checked_word -> edit_word_list -> size++;
                }else{
                    arr_size *= 2;
                    checked_word -> edit_word_list -> arr = realloc(checked_word -> edit_word_list -> arr, sizeof(char *) * arr_size);
                }
            }

            //if a new minimum edit_distance is found then we erase the array of edit_word_list -> arr, and continue
            //with the new edit_dist as edit distance minimum
            if(checked_word -> dist > edit_dist){
                checked_word -> dist = edit_dist;
            
                free(checked_word -> edit_word_list -> arr);    
                arr_size = 10;
                checked_word -> edit_word_list -> arr = malloc(sizeof(char *) * arr_size);
                
                checked_word -> edit_word_list -> arr[0] = w2;
                checked_word -> edit_word_list -> size = 1;
            }
        }
        print_list(fp, checked_word);
        free_matrix(edit_table, w1);
        free_wordlist(checked_word);
    }
    fclose(fp);
}