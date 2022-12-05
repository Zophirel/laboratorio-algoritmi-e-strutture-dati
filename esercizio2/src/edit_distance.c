#include "edit_distance.h"

int min(int x, int y)
{
    if(x < y)
        return x;
    return y;
}

//"right" to "left" approach of dynamic edit distance
int dynamic_edit_distance(char * word1, char * word2, int first_len, int second_len, int **rec_matrix)
{
    ///if the first word is empty we return the second lenght of the second one
    //since it would be only inserion
    if (first_len == 0)
        return (int)second_len;
 
    //same thing but for the second word
    if (second_len == 0)
        return (int)first_len;
 
    //if the cell is greater then -1 it means that the value of the comparison has already been calucalated
    //by the previous calls so we need just to return it
    if (rec_matrix[first_len - 1][second_len - 1] > -1)
        return rec_matrix[first_len - 1][second_len - 1];
 
    //if the current char is the same on both strings we need just to continue the recursion (so ingore tha same char)
    if (word1[first_len - 1] == word2[second_len - 1])
        return rec_matrix[first_len - 1][second_len - 1] = dynamic_edit_distance(word1, word2, first_len - 1, second_len - 1, rec_matrix);
 
    //last case we need to actually calculate the edit distance of the current char
    int insert = dynamic_edit_distance(word1, word2, first_len, second_len - 1, rec_matrix);
    int delete = dynamic_edit_distance(word1, word2, first_len - 1, second_len, rec_matrix);
    int replace = insert + delete;
    return rec_matrix[first_len - 1][second_len - 1] = 1 + min(min(insert, delete), replace);
}

//left to right edit_distance approach 
long unsigned int recursive_edit_distance(char* word1, char* word2){

    long unsigned int len1 = strlen(word1), len2 = strlen(word2);

    if(word1 == NULL || len1 == 0) 
        return len2;
        
    if(word2 == NULL || len2 == 0)
        return len1;
    
    if(*word1 == *word2)
        return recursive_edit_distance(word1+1, word2+1);

    long unsigned int deleteCost = 1 + recursive_edit_distance(word1, word2+1);
    long unsigned int insertCost = 1 + recursive_edit_distance(word1+1, word2);
    long unsigned int minCost;
    
    if (insertCost < deleteCost)   
        minCost = insertCost;
    else    
        minCost = deleteCost;

    return minCost;
}

