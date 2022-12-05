#include "ordered_array.h"

struct _OrderedArray{
    void **record;                  //it contains all the lines
    void **cmp_col;                 //it contains only the values of the column that has to be compred
    unsigned long size;             //current size of the struct
    unsigned long capacity;         //current malloc'd max size of the struct
    int (*precedes) (void*, void*); //function used to order cmp_col values
};


void setup(FILE *fp){
    int order;
    int c;
    int (*precedes) (void*, void*);

    OrderedArray *myarr = NULL;

    printf("Choose the order to sort (0 - ASC, 1 - DESC): ");
    while ((scanf("%d", &order) != 1) || (order != 0 && order != 1)) {
        while((c = getchar()) != '\n');
        fprintf(stderr, "plese enter 0 for ASC order or 1 to DESC order: ");
    }
    
    unsigned long int subseq;
    printf("Choose with how many sub list the csv has to be sort (>= 0): ");
    while (scanf("%lu", &subseq) != 1) {
        while((c = getchar()) != '\n');
        fprintf(stderr, "plese enter a valid number (>= 0): ");
    }

    int save;
    printf("Do you want to save the result? (0 - No, 1 - Yes): ");
    while ((scanf("%d", &save) != 1) || (save != 0 && save != 1)) {
        while((c = getchar()) != '\n');
        fprintf(stderr, "plese enter 0 for No or 1 for Yes: ");
    }

    int type;
    printf("Which type of elements do you want to sort (0 - Strings, 1 - Integers, 2 - Floats): ");
    while ((scanf("%d", &type) != 1) || (type != 0 && type != 1 && type != 2)) {
        while((c = getchar()) != '\n');
        fprintf(stderr, "plese enter 0 for Strings, 1 for Integers, 2 for Floats: ");
    }

    if(type == 0){
        precedes = (string_compare);
    }else if(type == 1){
        precedes = (int_compare);
    }else{
        precedes = (double_compare);
    }

    int column;
    printf("On which column are the value located: ");
    while ((scanf("%d", &column) != 1) || (column <= 0)) {
        while((c = getchar()) != '\n');
        fprintf(stderr, "plese insert a right column: ");
    }
    
    myarr = ordered_array_init(precedes, 100);
    myarr = ordered_array_load_csv(myarr, fp, column); 
    merge_binary_insertion_sort(myarr, subseq, order, save);
    ordered_array_free(myarr);
}

int main(int argc, char const *argv[])
{
    if(argc < 2){
        printf("file not inserted\n");
        exit(EXIT_FAILURE);
    }
    
    FILE *fp = NULL; 
    fp = fopen(argv[1], "r");
    
    if(fp == NULL){
        fprintf(stderr,"could not open the file\n");
        exit(1);
    }
    
    setup(fp);

    fclose(fp);
    return 0;
}
