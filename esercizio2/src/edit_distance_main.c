#include "edit_distance.h"

int main( int argc, char** argv ){
    if(argc != 3){
        fprintf(stderr, "files not found\n");
        return 0;
    }

    Words *correctme = collect_phrases(argv[1]);
    Words *dictionary = collection_dictionary(argv[2]);
    
    collection_edit_distance(correctme, dictionary);
    collection_free(correctme);
    collection_free(dictionary);
    return 0;
}