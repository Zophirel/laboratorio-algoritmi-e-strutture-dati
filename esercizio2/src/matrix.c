#include "edit_distance.h"

int **create_matrix(char *w1, char *w2){
    int **matrix;
    matrix = calloc((strlen(w1) + 1), sizeof(int *));

    for(long unsigned int i = 0; i < strlen(w1) + 1; i++){
        matrix[i] = calloc((strlen(w2) + 1), sizeof(int));
    }
    return matrix;
}

int **init_matrix(char * word1, char * word2, int **matrix){
    int len1 = (int)strlen(word1), len2 = (int)strlen(word2);
    for(int i = 0; i <= len1; i++){
        for(int j = 0; j <= len2; j++){
            matrix[i][j] = -1;
        }
    }
    return matrix;
}

void free_matrix(int **matrix, char *w1){
    for(int i = 0; i < (int)strlen(w1) + 1; i++)
        free(matrix[i]);
    free(matrix);
}

void show_matrix(int **m, char *w1, char *w2){
    int len1 = (int)strlen(w1), 
        len2 = (int)strlen(w2);
    
    for(int i = 0; i <= len1; i++){
        for(int j = 0; j <= len2; j++){
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}