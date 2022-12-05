#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "ordered_array.h"

struct _OrderedArray{
    void **record;                  //it contains all the lines
    void **cmp_col;                 //it contains only the values of the column that has to be compred
    unsigned long size;             //current size of the struct
    unsigned long capacity;         //current malloc'd max size of the struct
    int (*precedes) (void*, void*); //function used to order cmp_col values
};

int curr_col, ord, save_file;
long unsigned int dynamicSize = 100;

void ordered_array_free(OrderedArray *ordered_array){  
    for(unsigned long i = 0; i < ordered_array -> size; i++){
        free(ordered_array -> record[i]);
        free(ordered_array -> cmp_col[i]);
        ordered_array -> record[i] = NULL;
        ordered_array -> cmp_col[i] = NULL; 
    }
    free(ordered_array -> record);
    free(ordered_array -> cmp_col);
    free(ordered_array);
    ordered_array -> record = NULL;
    ordered_array -> cmp_col = NULL;
    ordered_array = NULL;
}

//check the status of malloced memory
void check_mem(OrderedArray *ordered_array, void **array, int sel){
    if(ordered_array == NULL && sel == 0){
        fprintf(stderr, "check_mem: unable to allocate memory for the ordered array struct\n");
        exit(EXIT_FAILURE);
    }
    
    if(array == NULL && sel == 1){
        fprintf(stderr, "check_mem: unable to allocate memory for the ordered array arrays\n");
        exit(EXIT_FAILURE);
    }
    return;
}

OrderedArray *ordered_array_init(int (*precedes)(void*, void*), unsigned long initialSize){
    OrderedArray *ordered_array = NULL;
    ordered_array = malloc(sizeof(OrderedArray));
    check_mem(ordered_array, NULL, 0);
    ordered_array -> record = malloc(initialSize * sizeof(void *));
    check_mem(NULL, ordered_array -> record, 1);
    ordered_array -> cmp_col = malloc(initialSize * sizeof(void *));
    check_mem(NULL, ordered_array -> cmp_col, 1);
    ordered_array -> size = 0;
    ordered_array -> capacity = initialSize;
    ordered_array -> precedes = precedes;
    return ordered_array;
}

void ordered_array_realloc(OrderedArray *ordered_array, unsigned long int size){
    ordered_array -> record = realloc(ordered_array -> record, size * sizeof(void *));
    check_mem(ordered_array, ordered_array -> record, 1);
    
    ordered_array -> cmp_col = realloc(ordered_array -> cmp_col, size * sizeof(void *));
    check_mem(ordered_array, ordered_array -> cmp_col, 1);
    
    ordered_array -> capacity = dynamicSize;
}

void ordered_array_show(OrderedArray *arr){
    for(unsigned long i = 0; i < arr->size; i++){
        printf("%s\n", (char *)arr->record[i]);
    }
    printf("\n");
}

//save the results into a file
void ordered_array_save(OrderedArray *arr){
    char file[128] = "ordered_record";
    char num = (char)((int) curr_col-1 + '0');
    char ext[5] = ".csv";
    strncat(file, &num, 1);
    strcat(file, ext);
    FILE *fp_w = fopen(file, "w");
    for(unsigned long i = 0; i < arr -> size; i++){
        fprintf(fp_w, "%s\n", (char *)arr -> record[i]);
    }
    fclose(fp_w);
}

//Precedes functions
int string_compare(void * a, void * b){
	if(ord == 0)
        return strcmp(a,b) <= 0;
    else
        return strcmp(a,b) >= 0;
}

int int_compare(void * a, void * b){ 
    int *minuendo = a;
    int *sottraendo = b;
    if(ord == 0)
        return (*minuendo - *sottraendo) <= 0;
    else
        return (*minuendo - *sottraendo) >= 0;
}

int double_compare(void * a, void * b){
    double *minuendo = a;
    double *sottraendo = b;
    if(ord == 0)
        return (*minuendo - *sottraendo) <= 0;
    else
        return (*minuendo - *sottraendo) >= 0;
}

void array_fill(OrderedArray *ordered_array, void *r_record, void *r_cmp_col){
    ordered_array -> record[ordered_array -> size] = r_record;
    ordered_array -> cmp_col[ordered_array -> size] = r_cmp_col;
    ordered_array -> size++;
}

//it tells how many colum there are in the loaded csv and it prevent
//to continue the execution if the csv is empty
int tot_col(char *temp){

    int i = 0;
    int num_col = 0;
    while(temp[i] != '\n'){
        if(temp[i] == ','){
            num_col++;
        }
        i++;
    }

    return num_col+1;
}

OrderedArray *ordered_array_load_csv(OrderedArray *arr, FILE * fp, int col){
    curr_col = col;  
    int firstline = 0;
    if (fp == NULL)
    {
        fprintf(stderr, "could not open the file"); 
        fclose(fp);
        exit(EXIT_FAILURE);
        return 0;
    }

    char entry[100];
    while(fgets(entry, 100, fp) && entry[0] != '\n'){         

        if(firstline == 0){
            char temp[100];
            strncpy(temp, entry, 100);
            int ncol = tot_col(temp);
            if(curr_col > ncol){
                fprintf(stderr, "ordered_array_read_csv: there are no other field to sort");
                exit(EXIT_FAILURE);
            }
            firstline = 1;
        }
        
        if(arr -> size == arr -> capacity-1){
            dynamicSize *=2;
            ordered_array_realloc(arr, dynamicSize);
        }
        
        char *line = strdup(entry);
        char *r_record = strtok(entry, "\n");

        strtok(line, ",");
        for(int i = 2; i < curr_col; i++)
            strtok(NULL, ",");
        
        char *r_cmp_col = strtok(NULL, ",");
        if(arr -> precedes == (string_compare))
            array_fill(arr, strdup(r_record), strdup(r_cmp_col));
        
        else if(arr -> precedes == (int_compare)){     
            
            int *value = malloc(sizeof(int *));
            *value = atoi(r_cmp_col);
            array_fill(arr, strdup(r_record), value);
            
        }else if(arr -> precedes == (double_compare)){
            
            double *value = malloc(sizeof(double *));
            *value = atof(r_cmp_col);
            array_fill(arr, strdup(r_record), value);
        }
        
        free(line);
    }

    return arr;
}

//extract the value from a given line
void *get_the_value(void *line){
    strtok(line, ",");
    for(int i = 2; i < curr_col; i++)
        strtok(NULL, ",");
    void *a = strtok(NULL, ",");
    return a;
}